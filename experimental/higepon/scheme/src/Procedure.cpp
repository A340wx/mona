#include "Procedure.h"

using namespace monash;

Procedure::Procedure(Lambda* lamba, Environment* env) : env_(env)
{
    body_ = lamba->body();
    parameters_ = new Variables();
    Variables* lparameters = lamba->parameters();
    for (Variables::iterator it = lparameters->begin(); it != lparameters->end(); it++)
    {
        parameters_->push_back(*it);
    }
}

Procedure::~Procedure()
{
    delete parameters_;
}

std::string Procedure::toString()
{
    return "procedure : " + body_->at(0)->toString();
}

int Procedure::type() const
{
    return Object::PROCEDURE;
}

Object* Procedure::eval(Environment* env)
{
    printf("don't eval procedure!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!%s %s:%d\n", __func__, __FILE__, __LINE__);fflush(stdout);// debug
    return this;
}