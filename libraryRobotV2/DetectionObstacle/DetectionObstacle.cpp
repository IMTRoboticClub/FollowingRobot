#include "DetectionObstacle.h"

DetectionObstacle::DetectionObstacle(int pinTrig, int pinEcho)
{
    m_pinTrig = pinTrig;
    m_pinEcho = pinEcho;
}

void DetectionObstacle::setup()
{
    pinMode(m_pinTrig, OUTPUT);
    digitalWrite(m_pinTrig, LOW);
    pinMode(m_pinEcho, INPUT);
}

long DetectionObstacle::recupDistanceCM()
{
    digitalWrite(m_pinTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_pinTrig, LOW);
    long lecture_echo = pulseIn(m_pinEcho, HIGH);
    long cm = lecture_echo / 58; 

    return cm;
}

float DetectionObstacle::recupDistanceM()
{
    return recupDistanceCM()/100;
}