#include<iostream>
#include<cmath>
#include<string>
using namespace std;
struct node//структура записи
{
    int Key;//ключ char/int/string нет разницы
    int Count;//счетчик
    node* Left;//левое поддерево
    node* Right;//правое поддерево
};
int sum = -1;//колличество элементов левого поддерева(-1 из за корня дерева)
string *str;//3 задание, массив стрингов
class TREE
{
private:
    node* duk; //Корень дерева.
public:
    TREE() { duk = NULL; }
    node** GetDuk() { return &duk; }//через метод возвращает обьект
    node* Tree(int, node**);//конструктор класса
    void Vyvod(node**, int);//боковой вывод дерева
    void VyvodVertical(node**, int);//вертикальный вывод дерева
    void Search(node**, int,int);//поиск элемента и вывод его уровня(начиная с 0)
    void Sum(node**,bool);//счетчик количества элементов левого поддерева
    int Level(node*);//счетчик глубины
};
int main()
{
    setlocale(LC_ALL, "Russian");//вывод русского в консоль
    TREE A;
    int n,search,menu=1;
    
    cout << "Введите количество вершин -...\n"; cin >> n;
    cout << "Вводите ключи...\n";
    int deep = 3;
    A.Tree(n, A.GetDuk()); 
    A.Vyvod(A.GetDuk(), 0);
    deep = A.Level(*A.GetDuk());
    while (menu) {
        cout << "Введите номер действия,0-закрыть программу,1-поиск глубины элемента,2- подсчет левого поддерева,3-вывести вертикально дерево...\n"<<endl;
        cin >> menu;
        switch (menu) {//консольное меню
        case 1://поиск глубины
            cout << "Введите значение поиска...\n";
            cin >> search;
            A.Search(A.GetDuk(), search, 0);
            break;
        case 2://количество элементов левого поддерева
            A.Sum(A.GetDuk(), 0);
            cout <<endl<<sum<<endl;
            break;
        case 3://вертикальный вывод
            if (n == 1) { A.Vyvod(A.GetDuk(), 0); break; }
            str = new string[deep];//выделение памяти под динамический массив
            for (int i = deep-1; i >= 0; i--)
            {
                str[i] ="";//обнуление элементов
            }
            A.VyvodVertical(A.GetDuk(), deep);
            for (int i = deep-1; i >=0; i--)
            {
                cout << str[i]<<endl;//вывод элементов массива
            }
            break;
        case 0: 
            return 0; //выход из программы
            break;
        default:
            cout << "Ввели некорректное значение" << endl;
            break;
        }
    }
   
    return 0;
}

node* TREE::Tree(int n, node** p)
// Построение идеально сбалансированного
//           дерева с n вершинами.
// *p - указатель на корень дерева.
{
    node* now;
    int x, nl, nr;

    now = *p;
    if (n == 0) *p = NULL;
    else
    {
        nl = n / 2;
        nr = n - nl - 1;
        cin >> x;
        now = new(node);
        (*now).Key = x;
        Tree(nl, &((*now).Left));//переход к левому поддереву
        Tree(nr, &((*now).Right));//переход к правому поддереву
        *p = now;
    }
    return now;
}

void TREE::Vyvod(node** w, int l)
// Изображение бинарного дерева, заданного
// указателем *w на экране дисплея.
{
    if (*w != NULL)
    {
        Vyvod(&((**w).Right), l + 1);
        for (int i = 1; i <= l; i++) cout << "   ";
        cout << (**w).Key << endl;
        Vyvod(&((**w).Left), l + 1);
    }
}
void TREE::Search(node** w,int search,int count)
// поиск
{
    
    if ((**w).Key != search)//проход по дереву
    {
        count++;
        if ((**w).Right != NULL)Search(&((**w).Right), search, count);
        if ((**w).Left != NULL)Search(&((**w).Left), search, count);
    }
    else if ((**w).Key == search) {//искомый элемент
        cout << endl << count << endl;
        return;
    }
    else return;
}
void TREE::Sum(node** w,bool flag)
// колиество элементов левого поддерева
{
    
    sum++;
    if ((**w).Right != NULL && flag ) Sum(&((**w).Right),1);
    if ((**w).Left != NULL)Sum(&((**w).Left),1);
    return;
}
void TREE::VyvodVertical(node** w, int deep=0)
// Изображение бинарного дерева, заданного
// указателем *w на экране дисплея вертикально.
{

    if (*w != NULL)
    {   
        for (int i = 1; i < pow(2,deep); i++) str[deep-1] += ' ';
        str[deep-1]+=to_string((**w).Key);//вывод элемента
        if((**w).Key>9) for (int i = 1; i < pow(2, deep); i++) str[deep - 1] += ' ';//проверка на количество цифр, для красивого вывода
        else for (int i = 1; i <= pow(2,deep); i++) str[deep-1] += ' ';
       if(&((**w).Left)!=NULL) VyvodVertical(&((**w).Left), deep-1);
       if(&((**w).Right) != NULL)VyvodVertical(&((**w).Right), deep-1);
    }
}
int TREE::Level(node* cur_node) {
    if (!cur_node) {
        return 0; // Возвращаем, если у нас нет уровня
    }
    return 1 + max(Level(cur_node->Left), Level(cur_node->Right));//ищем макс глубину дерева
}
