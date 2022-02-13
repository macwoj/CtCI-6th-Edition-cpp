#include <iostream>
#include <string>
#include <memory>
#include <list>
using namespace std;

class Animal {
    string name_;
    int timestamp_;
public:
    Animal(string n,int t):name_(n),timestamp_(t) {}
    int timestamp() { return timestamp_; }
    void print() {
        cout << name_ << " " << timestamp() << endl;
    }
};

using animalPtr = shared_ptr<Animal>;

class Cat: public Animal {
public:
    Cat(string n,int t): Animal(n,t) {}
};

class Dog: public Animal {
public:
    Dog(string n,int t): Animal(n,t) {}
};

class AnimalQueue {
    list<animalPtr> dogs_;
    list<animalPtr> cats_;
public:
    void push(Dog d) {
        dogs_.push_back(make_shared<Dog>(d));
    }
    void push(Cat c) {
        cats_.push_back(make_shared<Cat>(c));
    }

    animalPtr any() {
        bool oldDog = false;
        bool oldCat = false;
        if (!dogs_.empty() && !cats_.empty()) {
            if (dogs_.front() < cats_.front()) {
                oldDog = true;
            } else {
                oldCat = true;
            }
        }
        else if (!dogs_.empty()) {
            oldDog = true;
        }
        else if (!cats_.empty()) {
            oldCat = true;
        }
        if (oldDog) {
            auto a = dogs_.front();
            dogs_.pop_front();
            return a;
        }
        if (oldCat) {
            auto a = cats_.front();
            cats_.pop_front();
            return a;
        }
        return {};
    }

    animalPtr dog() {
        if (!dogs_.empty()) {
            auto a = dogs_.front();
            dogs_.pop_front();
            return a;
        }
        return {};
    }

    animalPtr cat() {
        if (!cats_.empty()) {
            auto a = cats_.front();
            cats_.pop_front();
            return a;
        }
        return {};
    }
};

int main() {
    {
        AnimalQueue q;
        q.push(Cat("cat",1));
        q.push(Cat("cat",2));
        q.push(Dog("dog",3));

        q.any()->print();
        q.any()->print();
        q.any()->print();
    }
    {
        AnimalQueue q;
        q.push(Cat("cat",1));
        q.push(Cat("cat",2));
        q.push(Dog("dog",3));

        q.dog()->print();
        q.any()->print();
        q.any()->print();
    }
}