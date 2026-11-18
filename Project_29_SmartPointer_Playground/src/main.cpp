#include <iostream>

template<typename T>
class SimpleUniquePtr {
public:
    // Constructors
    SimpleUniquePtr() = default;
    explicit SimpleUniquePtr(T* p) : ptr(p) {}; // Need to be explicit to avoid implicit conversions

    // Copy constructor and copy assignment operator are deleted to prevent copying
    SimpleUniquePtr(const SimpleUniquePtr&) = delete;
    SimpleUniquePtr& operator=(const SimpleUniquePtr&) = delete;

    // Move constructor
    SimpleUniquePtr(SimpleUniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr; // Prevent double deletion
    }

    // Move assignment operator
    SimpleUniquePtr& operator=(SimpleUniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // Overload dereference operator
    T& operator*() {
        return *ptr;
    }

    // Overload arrow operator
    T* operator->() {
        return ptr;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }

    bool operator==(std::nullptr_t) const {
        return ptr == nullptr;
    }

     bool operator!=(std::nullptr_t) const {
        return ptr != nullptr;
    }

    // Destructor
    ~SimpleUniquePtr(){
        delete ptr;
    };

private:
    T* ptr;
};

int main() {
    SimpleUniquePtr<int> myPtr(new int(42));
    std::cout << *myPtr << std::endl;

    SimpleUniquePtr<int> anotherPtr = std::move(myPtr);
    if(myPtr != nullptr) {
        std::cout << "myPtr is not null" << std::endl;
    } else {
        std::cout << "myPtr is null" << std::endl;
    }

    std::cout << *anotherPtr << std::endl;

    return 0;
}