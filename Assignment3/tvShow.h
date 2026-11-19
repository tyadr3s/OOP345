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

#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include "mediaItem.h"


namespace seneca{
    class TvShow;

    struct TvEpisode
    {
        const TvShow* m_show{};
        unsigned short m_numberOverall{};
        unsigned short m_season{};
        unsigned short m_numberInSeason{};
        std::string m_airDate{};
        unsigned int m_length{};
        std::string m_title{};
        std::string m_summary{};
    };

    class TvShow : public MediaItem {
        std::string m_id;
        std::vector<TvEpisode> m_episodes;
        TvShow(const std::string& id, const std::string& title, unsigned short year, const std::string& summary);

    public:
        void display(std::ostream& out) const override;
        static TvShow* createItem(const std::string& strShow);

        template<typename Collection_t>
        static void addEpisode(Collection_t& col,const std::string& strEpisode);

        double getEpisodeAverageLength() const;
        std::list<std::string> getLongEpisodes() const;
    };
    
    template<typename Collection_t>
    void TvShow::addEpisode(Collection_t& col, const std::string& line) {
        if (line.empty() || line[0] == '#') {
            throw "Not a valid episode.";
        }
        std::stringstream data(line);
        std::string id, number, season, episodeNumber;
        std::string airDate, length, title, summary;
        
        getline(data, id, ',');
        getline(data, number, ',');
        getline(data, season, ',');
        getline(data, episodeNumber, ',');
        getline(data, airDate, ',');
        getline(data, length, ',');
        getline(data, title, ',');
        getline(data, summary);

        trim(id);
        trim(number);
        trim(season);
        trim(episodeNumber);
        trim(airDate);
        trim(length);
        trim(title);
        trim(summary);
        
        if(season.empty()){
            season = "1";
        }
        std::stringstream time(length);
        int hours = 0;
        int minutes = 0;
        int seconds = 0;
        char colon;
        time >> hours >> colon >> minutes >> colon >> seconds;
        
        for (size_t i = 0; i < col.size(); i++) {
            TvShow* show = dynamic_cast<TvShow*>(col[i]);
            if (show != nullptr && show->m_id == id) {
                
                TvEpisode episode;
                episode.m_show = show;
                episode.m_numberOverall = stoi(number);
                episode.m_season = stoi(season);
                episode.m_numberInSeason = stoi(episodeNumber);
                episode.m_airDate = airDate;
                episode.m_length = hours * 3600 + minutes * 60 + seconds;
                episode.m_title = title;
                episode.m_summary = summary;
                show->m_episodes.push_back(episode);

                return;
            }
        }
    }

}
#endif
