#include "pch.h"
#include "Student.h"
#include <cstring> // For strncpy_s
#include <vector>

class Student {
public:
    Student(int id, const char* name, float score) : id(id), score(score) {
        strncpy_s(this->name, name, sizeof(this->name) - 1);
        this->name[sizeof(this->name) - 1] = '\0'; // Ensure null termination
    }

    int GetId() const { return id; }
    const char* GetName() const { return name; }
    float GetScore() const { return score; }

private:
    int id;
    char name[100];
    float score;
};

extern "C" {

    MYLIBRARY_API Student* CreateStudent(int id, const char* name, float score) {
        return new Student(id, name, score);
    }

    MYLIBRARY_API int GetStudentId(Student* student) {
        return student ? student->GetId() : -1;
    }

    MYLIBRARY_API const char* GetStudentName(Student* student) {
        return student ? student->GetName() : "";
    }

    MYLIBRARY_API float GetStudentScore(Student* student) {
        return student ? student->GetScore() : -1.0f;
    }

    MYLIBRARY_API void DestroyStudent(Student* student) {
        delete student;
    }

    MYLIBRARY_API std::vector<Student*>* CreateStudentCollection() {
        return new std::vector<Student*>();
    }

    MYLIBRARY_API void AddStudentToCollection(std::vector<Student*>* collection, Student* student) {
        if (collection && student) {
            collection->push_back(student);
        }
    }

    MYLIBRARY_API Student* GetStudentFromCollection(std::vector<Student*>* collection, int index) {
        if (collection && index >= 0 && index < collection->size()) {
            return (*collection)[index];
        }
        return nullptr;
    }

    MYLIBRARY_API int GetStudentCollectionSize(std::vector<Student*>* collection) {
        return collection ? static_cast<int>(collection->size()) : 0;
    }

    MYLIBRARY_API void DestroyStudentCollection(std::vector<Student*>* collection) {
        if (collection) {
            for (Student* student : *collection) {
                delete student;
            }
            delete collection;
        }
    }
}
