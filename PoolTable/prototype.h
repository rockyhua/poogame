#ifndef PROTOTYPE_H
#define PROTOTYPE_H
/**
 * @brief The Prototype class will give the child class a clone funtion, which is use for deep copy the object.
 */
class Prototype{
public:
    virtual Prototype* clone()=0;
};
#endif // PROTOTYPE_H
