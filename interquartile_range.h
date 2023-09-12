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
    //cout << "hi" << endl;
    Node* Fptr = head;
    Node* Sptr = head;
    Node* SSptr = head;

    float countF = 1.0f, countS = 1.0f, countSS = 1.0f;

    float temp1 = 0.0f, temp2 = 0.0f;
    float q1 = 0.0f, q3 = 0.0f, q2 = 0.0f;

    while (Fptr->next != nullptr) {
        if (Fptr->next->next != nullptr) {
            Fptr = Fptr->next->next;
            countF += 2.0f;
            Sptr = Sptr->next;
            countS++;
            //cout << "countS: " << countS << endl;
            //cout << "Sptr value: " << Sptr->value << endl;


            if (fmod(countS, 2.0f) == 1.0f && countS != 1.0f && Fptr->next != nullptr) {
                SSptr = SSptr->next;
                countSS++;
                //cout << "countSS: " << countSS << endl;
            }
        }
        else if (Fptr->next != nullptr) {
            Fptr = Fptr->next;
            countF++;
        }
    }

    if (fmod(countF, 4.0f) == 0.0f || fmod((countF - 1.0f) / 2.0f, 2.0f) == 0.0f) {
        temp1 = SSptr->value;
        SSptr = SSptr->next;
        countSS++;
        temp2 = SSptr->value;
        q1 = (temp1 + temp2) / 2;

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
    else {
        q1 = SSptr->value;

        for (float y = 0.0f; y < countSS; y++) {
            Sptr = Sptr->next;
            countS++;
        }
        q3 = Sptr->value;
        q2 = q3 - q1;

        
    }

    return q2;
}