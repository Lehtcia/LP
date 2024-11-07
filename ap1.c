#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node* next;
} Node;


Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


void insertEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}


void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}


void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void insertionSort(Node** head) {
    if (*head == NULL) return;

    Node* sorted = NULL;  
    Node* current = *head;  

    while (current != NULL) {
        Node* next = current->next;

       
        if (sorted == NULL || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            Node* temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }
    *head = sorted;
}

Node* findMin(Node* head) {
    Node* minNode = head;
    Node* current = head;
    while (current != NULL) {
        if (current->data < minNode->data) {
            minNode = current;
        }
        current = current->next;
    }
    return minNode;
}


void selectionSort(Node** head) {
    if (*head == NULL) return;

    Node* tempHead = *head;
    while (tempHead != NULL) {
        Node* minNode = findMin(tempHead);

        
        if (minNode != tempHead) {
            int tempData = tempHead->data;
            tempHead->data = minNode->data;
            minNode->data = tempData;
        }

        tempHead = tempHead->next;
    }
}

int findKthSmallest(Node* head, int k) {
    
    insertionSort(&head);

    
    Node* current = head;
    int count = 1;

    while (current != NULL) {
        if (count == k) {
            return current->data;
        }
        current = current->next;
        count++;
    }

    
    return -1;
}

int mergeAndCount(Node* left, Node* right, Node** mergedHead) {
    int inversions = 0;
    Node* temp = NULL;
    Node* currentLeft = left;
    Node* currentRight = right;


    while (currentLeft != NULL && currentRight != NULL) {
        if (currentLeft->data <= currentRight->data) {
            if (*mergedHead == NULL) {
                *mergedHead = currentLeft;
            } else {
                temp->next = currentLeft;
            }
            temp = currentLeft;
            currentLeft = currentLeft->next;
        } else {
            inversions += 1;
            if (*mergedHead == NULL) {
                *mergedHead = currentRight;
            } else {
                temp->next = currentRight;
            }
            temp = currentRight;
            currentRight = currentRight->next;
        }
    }


    if (currentLeft != NULL) {
        temp->next = currentLeft;
    }
    if (currentRight != NULL) {
        temp->next = currentRight;
    }

    return inversions;
}


int mergeSortAndCount(Node* head, Node** sortedHead) {
    if (head == NULL || head->next == NULL) {
        *sortedHead = head;
        return 0;
    }

    Node* middle = head;
    Node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        middle = middle->next;
        fast = fast->next->next;
    }

    Node* left = head;
    Node* right = middle->next;
    middle->next = NULL;

    int leftInversions = mergeSortAndCount(left, &left);
    int rightInversions = mergeSortAndCount(right, &right);
    int mergeInversions = mergeAndCount(left, right, sortedHead);

    return leftInversions + rightInversions + mergeInversions;
}
int main() {
    Node* list = NULL;
    insertEnd(&list, 5);
    insertEnd(&list, 2);
    insertEnd(&list, 9);
    insertEnd(&list, 1);
    insertEnd(&list, 4);
    insertEnd(&list, 7);

    printf("Lista original: ");
    printList(list);

    insertionSort(&list);
    printf("Lista ordenada por inserção: ");
    printList(list);

    selectionSort(&list);
    printf("Lista ordenada por seleção: ");
    printList(list);

    int k = 3;
    int kthSmallest = findKthSmallest(list, k);
    printf("O %d-ésimo menor elemento é: %d\n", k, kthSmallest);

    Node* sortedHead = NULL;
    int inversions = mergeSortAndCount(list, &sortedHead);
    printf("Número de inversões: %d\n", inversions);

    freeList(list);
    return 0;
}
