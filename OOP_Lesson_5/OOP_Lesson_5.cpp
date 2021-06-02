#include <iostream>
#include <vector>
using namespace std;

//1.
//
//Реализовать шаблон класса Pair1, который позволяет пользователю передавать данные одного типа парами.
//Следующий код :
//int main()
//{
//    Pair1<int> p1(6, 9);
//    cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
//
//    const Pair1<double> p2(3.4, 7.8);
//    cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
//
//    return 0;
//}
//
//
//… должен производить результат :
//Pair: 6 9
//Pair : 3.4 7.8

template<class T>
class Pair1
{
private:
    T m_first;
    T m_second;
public:
    Pair1(T first, T second) : m_first(first), m_second(second) { }
    T first() const { return m_first; }
    T second() const { return m_second; }
};

//2.
//Реализовать класс Pair, который позволяет использовать разные типы данных в передаваемых парах.
//Следующий код :
//int main()
//{
//    Pair<int, double> p1(6, 7.8);
//    cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
//
//    const Pair<double, int> p2(3.4, 5);
//    cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
//
//    return 0;
//}
//
//
//… должен производить следующий результат :
//Pair: 6 7.8
//Pair : 3.4 5
//Подсказка : чтобы определить шаблон с использованием двух разных типов, просто разделите параметры типа шаблона запятой.

template <class T1, class T2>
class Pair
{
private:
    T1 m_first;
    T2 m_second;
public:
    Pair(T1 first, T2 second) : m_first(first), m_second(second) { }
    T1 first() const { 
        return m_first; 
    }
    T2 second() const { return m_second; }
};


//3.
//Написать шаблон класса StringValuePair, в котором первое значение всегда типа string, а второе — любого типа.
// Этот шаблон класса должен наследовать частично специализированный класс Pair, в котором первый параметр — string, а второй — любого типа данных.
//
//Следующий код :
//int main()
//{
//    StringValuePair<int> svp("Amazing", 7);
//    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
//    return 0;
//}
//
//
//… должен производить следующий результат :
//Pair: Amazing 7
//Подсказка : при вызове конструктора класса Pair из конструктора класса StringValuePair не забудьте указать, что параметры относятся к классу Pair.


template <class T>
class StringValuePair : public Pair<string, T>
{
public:
    StringValuePair(string first, T second) : Pair<string, T>(first, second) {}
};



//4.
//Согласно иерархии классов, которая представлена в методичке к уроку 3, от класса Hand наследует класс GenericPlayer, 
//который обобщенно представляет игрока, ведь у нас будет два типа игроков - человек и компьютер.Создать класс GenericPlayer, 
//в который добавить поле name - имя игрока.Также добавить 3 метода:
//IsHitting() - чисто виртуальная функция, возвращает информацию, нужна ли игроку еще одна карта.
//IsBoosted() - возвращает bool значение, есть ли у игрока перебор
//Bust() - выводит на экран имя игрока и объявляет, что у него перебор.


enum eSuit { CLUBS, SPADES, DIAMONDS, HEARTS }; //крести, пики, буби, черви
enum eRank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };

class Card
{
    eSuit m_suit;
    eRank m_rank;
    bool m_isFaceUp;
public:
    Card(eSuit suit, eRank value, bool pos) : m_suit(suit), m_rank(value), m_isFaceUp(pos) {}
    void flip() { m_isFaceUp = !m_isFaceUp; }
    int getValue() 
    {
        int value = 0;
        if (m_isFaceUp)
        {
            value = m_rank;
            if (value > 10)
            {
                value = 10;
            }
        }
        return value;
    }
};


class Hand
{
private:
    vector<Card*> m_cards; //колода карт
public:
    Hand() { m_cards.reserve(7); }
    virtual ~Hand() { clear(); }
    void add(Card* pCard) { m_cards.push_back(pCard); }
    void clear() 
    { 
        vector<Card*>::iterator iter = m_cards.begin();
        for (iter = m_cards.begin(); iter != m_cards.end(); ++iter)
        {
            delete *iter;
            *iter = 0;
        }
        m_cards.clear();
    }
    int getTotal()
    {

        if (m_cards.empty()) 
        {
            return 0;
        }
        if (m_cards[0]->getValue() == 0)
        {
            return 0;
        }

        int s = 0;
        int acesNum = 0;
        for (Card* c : m_cards)
        {
            int val = c->getValue();
            if (val == ACE) acesNum++;
            s += val;
        }
        if (acesNum < 2) //Если вдруг тузов больше 1, нет смысла их считать как 11
        {
            if ((s + 10) <= 21) //Пробуем считать туз как 11, поэтому добавляем к общей сумме 10
                s += 10;
        }
        return s;
    }
};


class GenericPlayer : public Hand
{
private:
    string m_playerName;
public:
    virtual bool isHitting() = 0;
    bool isBoosted() 
    {
        return getTotal() > 21;
    }

    void bust()
    {
        cout << m_playerName << " busted" << endl;
    }
};



int main()
{
    cout << "Task 1" << endl;
    Pair1<int> p1(6, 9);
    cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair1<double> p2(3.4, 7.8);
    cout <<  "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    cout << endl << "Task 2" << endl;
    Pair<int, double> p1_(6, 7.8);
    cout << "Pair: " << p1_.first() << ' ' << p1_.second() << '\n';
    
    const Pair<double, int> p2_(3.4, 5);
    cout << "Pair: " << p2_.first() << ' ' << p2_.second() << '\n';
    
    cout << endl << "Task 3" << endl;
    StringValuePair<int> svp("Amazing", 7);
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

    Hand hand;
    Card *c1 = new Card(SPADES, NINE, true);
    Card *c2 = new Card(SPADES, TWO, true);
    Card *c3 = new Card(SPADES, ACE, true);

    hand.add(c1);
    hand.add(c2);
    hand.add(c3);

    int v = hand.getTotal();
    cout << "Hand total score: " << v << endl;

    return 0;
}