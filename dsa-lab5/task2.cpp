#include <iostream>
#include <string>
using namespace std;

class PrintQueue {
private:
    struct Job {
        int    id;
        string docName;
        int    pages;
        Job*   next;
        Job(int i, const string& d, int p)
            : id(i), docName(d), pages(p), next(nullptr) {}
    };

    Job* front;
    Job* rear;
    int  count;

public:
    PrintQueue() : front(nullptr), rear(nullptr), count(0) {}
    ~PrintQueue() { clear(); }

    void addJob(int id, const string& doc, int pages) {
        Job* j = new Job(id, doc, pages);
        if (!rear) {               
            front = rear = j;
        } else {
            rear->next = j;        
            rear = j;                
        }
        count++;
        cout << "Added job " << id << " (" << doc << ")\n";
    }

    void processJob() {
        if (!front) {
            cout << "Queue is empty — nothing to process.\n";
            return;
        }
        Job* temp = front;
        cout << "Processing Job " << temp->id
             << " , " << temp->docName
             << " , " << temp->pages << " pages\n";
        front = front->next;
        if (!front) rear = nullptr;  
        delete temp;
        count--;
    }

    void viewNext() const {
        if (!front) { cout << "No job waiting.\n"; return; }
        cout << "Next job: ID=" << front->id
             << ", Doc=" << front->docName
             << ", Pages=" << front->pages << "\n";
    }

    void display() const {
        if (!front) { cout << "Queue is empty.\n"; return; }
        cout << "Front - ";
        Job* cur = front;
        while (cur) {
            cout << "[" << cur->id << ":" << cur->docName
                 << ":" << cur->pages << "p]";
            if (cur->next) cout << " - ";
            cur = cur->next;
        }
        cout << " <- Rear\n";
    }

    int countJobs() const { return count; }

    bool isEmpty() const { return front == nullptr; }

    void clear() {
        while (front) {
            Job* temp = front;
            front = front->next;
            delete temp;
        }
        front = rear = nullptr;
        count = 0;
    }
};

int main() {
    PrintQueue q;

    cout << " Adding Jobs \n";
    q.addJob(101, "Assignment1.pdf", 10);
    q.addJob(102, "Report.docx",     25);
    q.addJob(103, "Notes.pdf",        5);
    q.addJob(104, "LabTask.docx",    15);

    cout << "\n1. Display all jobs:\n";
    q.display();

    cout << "\n2. Process two jobs:\n";
    q.processJob();
    q.processJob();

    cout << "\n3. Display remaining jobs:\n";
    q.display();

    cout << "\n4. Add a new job:\n";
    q.addJob(105, "Slides.pptx", 8);
    q.display();

    cout << "\n5. View next job:\n";
    q.viewNext();

    cout << "\n6. Process all remaining jobs:\n";
    while (!q.isEmpty()) q.processJob();

    cout << "\n7. Try to process from empty queue:\n";
    q.processJob();

    cout << "\nFinal count: " << q.countJobs() << "\n";
    return 0;
}