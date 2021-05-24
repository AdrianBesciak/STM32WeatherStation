#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>
#include "weather.hpp"

class ModelListener
{
public:
    ModelListener() : model(nullptr) {}
    
    virtual ~ModelListener() = default;

    void bind(Model* m)
    {
        model = m;
    }

    virtual void temperatureChanged(float temp) {};
    virtual void weatherChanged(weather_t* weatherStruct) {};
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
