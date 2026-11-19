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
#include "tvShow.h"
#include "settings.h"
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <iterator>

namespace seneca
{

    TvShow::TvShow(const std::string &id, const std::string &title, unsigned short year, const std::string &summary) : MediaItem(title, summary, year), m_id(id){
    }

    TvShow *TvShow::createItem(const std::string &line){
        if (line.empty() || line[0] == '#'){
            throw "Not a valid show.";
        }
        std::stringstream data(line);
        std::string id, title, year, summary;

        getline(data, id, ',');
        getline(data, title, ',');
        getline(data, year, ',');
        getline(data, summary);

        trim(id);
        trim(title);
        trim(year);
        trim(summary);
        return new TvShow(id, title, static_cast<unsigned short>(stoi(year)), summary);
    }

    void TvShow::display(std::ostream &out) const
    {
        if (g_settings.m_tableView)
        {
            out << "S | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_episodes.size() << " | ";
            out << std::setw(4) << this->getYear() << " | ";
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
            for (auto &item : m_episodes)
            {
                out << std::setfill('0') << std::right;
                out << "    " << 'S' << std::setw(2) << item.m_season
                    << 'E' << std::setw(2) << item.m_numberInSeason << ' ';
                if (item.m_title != "")
                    out << item.m_title << '\n';
                else
                    out << "Episode " << item.m_numberOverall << '\n';

                pos = 0;
                while (pos < item.m_summary.size())
                {
                    out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
                    pos += g_settings.m_maxSummaryWidth - 8;
                }
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }
    
    double TvShow::getEpisodeAverageLength()const{
        if (m_episodes.empty()){
            return 0;
        }
        double total = std::accumulate(m_episodes.begin(), m_episodes.end(), 0.0,[](double sum, const TvEpisode& episode){
            return sum + episode.m_length;
        });
        return total / m_episodes.size();
    }
    
    std::list<std::string> TvShow::getLongEpisodes()const{
        std::list<TvEpisode> longEpisodes;
        std::list<std::string> titles;
        
        std::copy_if(m_episodes.begin(), m_episodes.end(),std::back_inserter(longEpisodes),[](const TvEpisode& episode){
            return episode.m_length >= 3600;
        });
        std::transform(longEpisodes.begin(), longEpisodes.end(),std::back_inserter(titles),[](const TvEpisode& episode){
            return episode.m_title;
        });
        return titles;
    }
}
