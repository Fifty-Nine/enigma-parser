#ifndef ENIGMA_DATE_H
#define ENIGMA_DATE_H

#include <QString>

namespace enigma
{

/*! Represents a date in an enigma file. */
class Date
{
public:
    /*! Constructs an invalid date. */
    Date();
    /*! Constructor.
     * \param [in] year_ The year.
     * \param [in] month_ The month.
     * \param [in] day_ The day.
     * \param [in] hour_ The hour. */
    Date(int year_, int month_, int day_, int hour_=-1);

    bool isValid() const;
    int year() const;
    int month() const;
    int day() const;
    int hour() const;

    /*! Parse the given string as a date.
     * \param[in] str The string to parse.
     * \return The parsed date. */
    static Date parse(const QString& str);

    QString toString() const;

private:
    int m_year;
    int m_month;
    int m_day;
    int m_hour;
};

} // namespace enigma

#endif // ENIGMA_DATE_H
