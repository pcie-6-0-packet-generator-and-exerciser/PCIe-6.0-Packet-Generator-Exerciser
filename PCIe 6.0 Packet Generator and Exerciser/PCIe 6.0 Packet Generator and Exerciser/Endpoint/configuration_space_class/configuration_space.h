class ConfigurationSpace
{
private:
    Register * head_;
    Register * tail_;
    int size_;

    /* Create a new node to store the value */
    void push(unsigned int v, Register_Name n, Register_Type t);

public:
    ConfigurationSpace();
};