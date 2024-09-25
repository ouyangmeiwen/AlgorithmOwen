#pragma once

#ifdef MYLIBRARY_EXPORTS
#define MYLIBRARY_API __declspec(dllexport)
#else
#define MYLIBRARY_API __declspec(dllexport)
#endif

#include <vector>

extern "C" {

    typedef struct Student Student;

    MYLIBRARY_API Student* CreateStudent(int id, const char* name, float score);
    MYLIBRARY_API int GetStudentId(Student* student);
    MYLIBRARY_API const char* GetStudentName(Student* student);
    MYLIBRARY_API float GetStudentScore(Student* student);
    MYLIBRARY_API void DestroyStudent(Student* student);

    MYLIBRARY_API std::vector<Student*>* CreateStudentCollection();
    MYLIBRARY_API void AddStudentToCollection(std::vector<Student*>* collection, Student* student);
    MYLIBRARY_API Student* GetStudentFromCollection(std::vector<Student*>* collection, int index);
    MYLIBRARY_API int GetStudentCollectionSize(std::vector<Student*>* collection);
    MYLIBRARY_API void DestroyStudentCollection(std::vector<Student*>* collection);
}
