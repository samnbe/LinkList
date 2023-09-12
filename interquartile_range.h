#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

class Node {
public:
    int value;
    Node* next = nullptr;
};

Node* insertEnd(Node* head, int key)
{
    Node* temp = new Node();
    temp->value = key;
    if (head == nullptr)
        head = temp;
    else
    {
        Node* curr = head;
        while (curr->next != nullptr)
            curr = curr->next;
        curr->next = temp;
    }
    return head;
}

float interQuartile(Node* head)
{
    //initialize fast, slow, and the very slow (SS) pointer 
    Node* Fptr = head;
    Node* Sptr = head;
    Node* SSptr = head;

    float countF = 1.0f, countS = 1.0f, countSS = 1.0f;
    float temp1 = 0.0f, temp2 = 0.0f;
    
    //q1 = lower bound, q3 = upper bound, q2 = interquartile range 
    float q1 = 0.0f, q3 = 0.0f, q2 = 0.0f;

    while (Fptr->next != nullptr) {
        //if the next next pointer is not null, move the fast pointer to the next next element in the linked list and move the slow pointer to the next element 
        if (Fptr->next->next != nullptr) {
            Fptr = Fptr->next->next;
            countF += 2.0f;
            Sptr = Sptr->next;
            countS++;

            //if the slow pointer count is odd and not 1, move the very slow pointer to the next element 
            if (fmod(countS, 2.0f) == 1.0f && countS != 1.0f && Fptr->next != nullptr) {
                SSptr = SSptr->next;
                countSS++;
            }
        }
        //if the next next element is null in the linked list, move fast pointer to the next element (if not null)
        else if (Fptr->next != nullptr) {
            Fptr = Fptr->next;
            countF++;
        }
    }

    //special cases when you divide NumElements - 1 by 2, and it gives you an even number
    //will have to take the median of 2 elements to get q1 and q3
    if (fmod(countF, 4.0f) == 0.0f || fmod((countF - 1.0f) / 2.0f, 2.0f) == 0.0f) {
        temp1 = SSptr->value;
        SSptr = SSptr->next;
        countSS++;
        temp2 = SSptr->value;
        q1 = (temp1 + temp2) / 2;

        //move slow pointer to q3 using q1 
        for (float i = 1.0f; i <= (countSS - 1.0f); i++) {
            Sptr = Sptr->next;
            countS++;
        }

        temp1 = Sptr->value;
        Sptr = Sptr->next;
        countS++;
        temp2 = Sptr->value;
        q3 = (temp1 + temp2) / 2;
        q2 = q3 - q1;
    }
    //normal cases, very slow pointer is on q1 
    else {
        q1 = SSptr->value;
        
        //move slow pointer to q3 using q1 
        for (float y = 0.0f; y < countSS; y++) {
            Sptr = Sptr->next;
            countS++;
        }
        
        q3 = Sptr->value;
        q2 = q3 - q1;
    }
    return q2;
}
