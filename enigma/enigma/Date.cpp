#include <cassert>
#include <QStringList>

#include "enigma/Date.h"

namespace enigma
{

Date::Date() :
    m_year(-1), m_month(-1), m_day(-1), m_hour(-1)
{ }

Date::Date(int year, int month, int day, int hour) :
    m_year(year), m_month(month), m_day(day), m_hour(hour)
{ }

bool Date::isValid() const
{
    return (m_year >= 0)
        && (m_month > 0) && (m_month <= 12)
        && (m_day > 0) && (m_day <= 31)
        && (m_hour >= -1) && (m_hour < 24);
}

int Date::year() const
{
    assert(m_year >= 0);
    return m_year;
}

int Date::month() const
{
    assert((m_month >= 0) && (m_month <= 12));
    return m_month;
}

int Date::day() const
{
    assert((m_day >= 0) && (m_day < 31));
    return m_day;
}

int Date::hour() const
{
    assert((m_hour >= -1) && (m_hour < 24));
    return m_hour;
}

Date Date::parse(const QString& str)
{
    QStringList parts = str.split('.');

    if ((parts.count() > 4) || (parts.count() < 3))
    {
        return Date();
    }

    QList<int> values;

    for (int i = 0; i < parts.count(); ++i)
    {
        bool ok = false;
        values << parts[i].toInt(&ok);

        if (!ok)
        {
            return Date();
        }
    }

    return Date(values[0], values[1], values[2],
        (values.count() == 4) ? values[3] : -1);
}

QString Date::toString() const
{
    QString result = QString::number(m_year) + "." + 
        QString::number(m_month) + "." + QString::number(m_day);

    if (m_hour > 0)
    {
        return result + "." + QString::number(m_hour);
    }

    return result;
}

} // namespace enigma
