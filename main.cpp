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
    List(): Head(NULL), Tail(NULL){};
    ~List();
    Node *Find(char NewWord[]);     //функция поиска элемента в списке
    void Add(char NewWord[]);       //добавление элемента в список
    void Del(Node *DelNode);        //удаление элемента из списка
    friend ostream& operator<<(ostream& st, const List& lst);
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
    Node *q = new Node;
    q->next = NULL;	
    strcpy(q->word,NewWord);
    if(Head != NULL)	//если в списке уже были элементы
    {
        q->prev = Tail;
        Tail->next = q;
        Tail = q;
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
        Head = DelNode->next;
        Head->prev = NULL;	
    }
    else if(Tail == DelNode)	//для случая, когда удаляемый элемент является хвостом списка
    {
        Tail = DelNode->prev;
        Tail->next = NULL;	
    }
    else			//для случая, если удаляемый элемент где-то в середине списка
    {
        Node *q = DelNode->prev;
        q->next = DelNode->next;
        q = DelNode->next;
        q->prev = DelNode->prev;
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

ostream& operator<<(ostream& st, const List& lst)
{
     Node *q = lst.Head;
      while (q != NULL)
     {
        st<< q->word << " ";
        q = q->next;
     }
     st << "\n";
     return st;
}



int main(int argc, char *argv[])
{
    List lst;

    ifstream file(argv[1]);
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
        cout << lst;
        file.close();
    }
    cin.get();
    return 0;
}
