#pragma once

#include <QObject>
#include <QtTest/QtTest>

class UnitTest : public QObject
{
    Q_OBJECT
public:
    explicit UnitTest(const std::string& name,QObject *parent = nullptr);

    std::string getName() const;

private:
    std::string name;
};
