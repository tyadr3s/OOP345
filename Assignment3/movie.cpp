/*
Name: Carlos Andres Ramirez Moreno
Seneca Email: caramirez-moreno@myseneca.ca
Student ID: 120847256
Date: November 18, 2026

I declare that this submission is the result of my own work
and I only copied the code that my professor provided to
complete my assignments. This submitted piece of work has
not been shared with any other student or 3rd party content
provider.
*/

#include "movie.h"
#include "settings.h"
#include <iomanip>
#include <sstream>

namespace seneca
{

    Movie::Movie(const std::string &title, unsigned short year, const std::string &summary) : MediaItem(title, summary, year)
    {
    }

    Movie *Movie::createItem(const std::string &line)
    {
        if (line.empty() || line[0] == '#')
        {
            throw "Not a valid movie.";
        }
        std::stringstream data(line);
        std::string title, year, summary;

        getline(data, title, ',');
        getline(data, year, ',');
        getline(data, summary);

        trim(title);
        trim(year);
        trim(summary);

        return new Movie(title, static_cast<unsigned short>(stoi(year)), summary);
    }

    void Movie::display(std::ostream &out) const
    {
        if (g_settings.m_tableView)
        {
            out << "M | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(9) << this->getYear() << " | ";
            out << std::left;
            if (g_settings.m_maxSummaryWidth > -1)
            {
                if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << this->getSummary();
                else
                    out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            }
            else
                out << this->getSummary();
            out << std::endl;
        }
        else
        {
            size_t pos = 0;
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }
}
