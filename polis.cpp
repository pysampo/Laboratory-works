#include <stdio.h>
#include <iostream>
#include <string.h>

#define SZ 50 //for str
#define PR priority(in[i]) //входной символ (input)
#define PR_H priority(st -> top()) //вершина стека
    
struct usel {
  char x;
  usel * next;
};

struct stack {
  usel * head;
  stack() {
    head = 0;
  }

  void push(char c) {
    usel * p = new usel;
    p -> x = c;
    p -> next = head;
    head = p; //вставка
  }
  char pop() {
    if (head) {
      usel * p = head;
      char c = p -> x;
      head = head -> next;
      delete p;
      return c; //вывод char + удаление
    }
  }

  char top() {
    char c;
    if (head) {
      c = head -> x;
      return c; 
      //вывод вершины char
    }
  }

  void _delete() {
    usel * p;
    while (head) {
      p = head;
      head = head -> next;
      delete p; 
      //удалить полностью одн. список (стэк)
    }
  }

  void head_delete() {
    usel * p = head;
    head = head  -> next;
    delete p; 
    //удаление только вершины
  }

  bool empty() {
    return head ? false : true; // ложно -> true.
  }

};

bool check(char a) {
 
  switch (a) {
  case '+':
    return true;
  case '-':
    return true;
  case '*':
    return true;
  case '/':
    return true;
  default:
    return false;
   }

}

int priority(char a) {

  switch (a) {
  case '(':
    return 1;
  case ')':
    return 2;
  case '+':
    return 3;
  case '-':
    return 3;
  case '*':
    return 4;
  case '/':
    return 4;
  default:
    return 0;
  }

}
void polis(char * in) {

  stack * st = new stack;

  bool ch_next = true; //флаг, false - если входное значение повторно встретил знак операции 
  bool fix = true; //флаг, false - если выражение записано неверно

  unsigned short skb_0 = 0;
  unsigned short skb_1 = 0;
  // для высчитывания количество скобок.
  if (check( in [0]) || check( in [strlen( in ) - 1])) {
    std::cout << "Error!"; //мини проверка перед обработкой. 
    //проверяем первое и последнее значения у выражения
    fix = false;
  } else {
    for (int i = 0; in[i]; i++) {
      if (!check(in[i]) && !isalpha(in[i]) && !isdigit(in[i]) && in[i] != '(' && in[i] != ')') {
        std::cout << '\n' << "Error, don't identification: " << in [i]; //если встречен иной символ в выражении 
        fix = false;
        break; // останавливаем цикл
      }
      //Алгортим Дейкстры. Заносим в стек только знаки операции, операнды выводим сразу.
      else if (isalpha(in[i]) || isdigit(in[i])) { //если встретили число или букву - считываем всё до знака операции
        while (true) { // операнды, включающиеся в себя числа и буквы - считаются переменными
          std::cout << in[i];
          if (!check(in[i])) break;
          i++;
        }
        ch_next = true;
      } else {
        //std::cout << ' '; // для читабельности многозначных чисел, переменных, состоящих из > 1 букв
        // PR   - priority(in[i]) //входной символ (input)
        // PR_H - priority(st -> top()) //вершина стека
        if (ch_next == false && PR != 1 && PR != 2) { //если предыдущее входное значение было знаком операции. (кроме скобок)
          std::cout << '\n' << "Error! Replace " << in [i] << " isn't correct" << '\n';
          fix = false;
          break;
        }
        if (st -> empty() && PR != 1) { //если стек пустой, то заносим сразу знак
          st -> push(in[i]);

        } else if (PR == 1) {
          skb_0++;
          st -> push(in[i]); //если это открывающая скобка, то заносим сразу в стэк

        } else if (PR == 2) {
          skb_1++; //не заносим в стэк закрывающую скобку
          while (st -> head) //!= nullptr
            if (PR_H == 1) {
              st -> head_delete(); //встретили открывающую скобку - удаляем его из стэка, и заканчиваем цикл.
              break;
            }
          else
            std::cout << st -> pop();
          ch_next = true;
          continue; //flag 
        } else {
          if (PR_H < PR) { //приоритет входного значения больше, чем у значения на вершине стэка
            st -> push(in[i]); // то заносим его в стэк
          } else if (PR_H >= PR) { //если приоритет вх. значения меньше или равно.(через иф для читабельности)
            while (PR_H >= PR && st -> head) //&& != nullptr 
            std::cout << st -> pop();
            //выталкиваем из стэка все значения, которые равны или больш вх.знач.                                                                         
            st -> push(in[i]); //заносим его в стэк
            //std::cout << ' ';// для читабельнсти многозначных

          }
        }
        ch_next = false;
      }
    }
  }
  if (skb_0 != skb_1) {
    std::cout << '\n' << "Error! '(' != ')' " << '\n';
    fix = false;
  }

  if (fix) {
    while (st -> head) {
        //std::cout << ' ' << st->pop(); //для читабельности многозначных 
        std::cout << st -> pop(); //выводим все значения в стеке 
      }
  } else
    st -> _delete(); //fix == false -> удаляем стек

}

int main(void) {

  char in [SZ] = {};
  std::cout << "Enter: " << '\n';
  std::cin >> in ;
  polis(in);

  return 0;
}
