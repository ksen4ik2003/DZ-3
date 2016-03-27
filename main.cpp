#include <iostream>
#include <fstream>
#include <cstring>


using namespace std;

struct Node
{
    char word[40];
    Node *next;
    Node *prev;
};

class List
{
    Node *Head, *Tail;  //голова и хвост списка
    public:
    List(): Head(NULL), Tail(NULL){};   //конструктор
    ~List();                            //деструктор
    Node *Find(char NewWord[]);     //функция поиска элемента в списке
    void Add(char NewWord[]);       //добавление элемента в список
    void Del(Node *DelNode);        //удаление элемента из списка
    void Show();                    //вывод на экран элементов списка
};

List::~List()
{
    while (Head)	//удаляем все элементы, начиная с головы, пока голова на что-то ссылается
    {
        Tail = Head->next;
        delete Head;
        Head = Tail;
    }
}

void List::Add(char NewWord[])
{
    Node *q = new Node;	//выделяем память под новый элемент списка
    q->next = NULL;	//указываем, что следующего элемента нет
    strcpy(q->word,NewWord);	//помещаем в новый элемент наше слово
    if(Head != NULL)	//если в списке уже были элементы
    {
        q->prev = Tail;	//для нового элемента указываем ссылку на предыдущий элемент - на хвост
        Tail->next = q;	//для последнего элемента указываем ссылку на след элемент - новый элемент
        Tail = q;	//изменяем хвост на новый элемент
    }
    else		//отдельный случай, когда список был пустой
    {
        q->prev = NULL;
        Head = Tail = q;
    }
}

void List::Del(Node *DelNode)
{
    if( (Head == DelNode) && (Tail == DelNode))	//для случая, когда удаляемый элемент является единственным
    {
        Head = NULL;
        Tail = NULL;
    }
    else if(Head == DelNode)	//для случая, когда удаляемый элемент является головой списка
    {
        Head = DelNode->next;	//делаем головой второй элемент
        Head->prev = NULL;	
    }
    else if(Tail == DelNode)	//для случая, когда удаляемый элемент является хвостом списка
    {
        Tail = DelNode->prev;	//делаем хвостом предпоследний элемент
        Tail->next = NULL;	
    }
    else			//для случая, если удаляемый элемент где-то в середине списка
    {
        Node *q = DelNode->prev;	//копируем указатель на предыдущий элемент
        q->next = DelNode->next;	//устанавливаем на него указатель следующего
        q = DelNode->next;		//копируем указатель на след элемент
        q->prev = DelNode->prev;	//устанавливаем на него указатель предыдущего
    }
    delete DelNode;	//освобождаем память от удаляемого элемента
}

Node *List::Find(char NewWord[])
{
    Node *q = Head;	//начиная с головы, проходимся по всем элементам, пока не найдем совпадение либо не дойдем до конца списка
    while(q && strcmp(q->word, NewWord))
        q = q->next;
    return q;
}

 void List::Show()
 {
     Node *q = Head; //Временно указываем на адрес первого элемента
      while (q != NULL) //Пока не встретим пустое значение
     {
        cout<< q->word << " "; //Выводим каждое считанное значение на экран
        q = q->next; //Смена адреса на адрес следующего элемента
     }
     cout << "\n";
}



int main(int argc, char *argv[])
{
    List lst;	//объявляем объект класса List

    ifstream file(argv[1]);	//открываем файл
    if(!file)
        cout << "File not opened";
    else
    {
        char strword[40];	//массивы для считывания слова из файла и его модификации
        char modstrword[40];

        Node *elem;
        while (!file.eof())
        {
            file >> strword;
            int i = 0;
            while(strword[i])
            {
                modstrword[i] = strword[i+1];
                i++;
            }
            if(strword[0] == '+')
            {
                elem = lst.Find(modstrword);
                if(!elem)
                    lst.Add(modstrword);
            }
            else if (strword[0] == '-')
            {
                elem = lst.Find(modstrword);
                if(elem)
                    lst.Del(elem);
            }
            else
            {
                elem = lst.Find(modstrword);
                if(elem)
                    cout << "yes " << modstrword <<"\n";
                else
                    cout << "no " << modstrword <<"\n";
            }
        }
        lst.Show(); //Отображаем получившийся список на экране
        file.close();
    }
    cin.get();
    return 0;
}
