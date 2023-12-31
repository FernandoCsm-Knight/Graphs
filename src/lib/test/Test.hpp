#ifndef MY_TEST_HPP
#define MY_TEST_HPP

class Test {
    protected:
        std::string name;
        std::string description;
        std::string path;

    public:
        Test(const std::string& path = "test.log", const std::string& name = "", const std::string& description = "") : name(name), description(description), path(path) {}
        virtual bool run() = 0;
};

#endif