#ifndef SENECA_SONGCOLLECTION_H
#define SENECA_SONGCOLLECTION_H
#include <iostream>
#include <string>
#include <vector>
#include <list>

namespace seneca {
    struct Song {
        std::string m_title;
        std::string m_artist;
        std::string m_album;
        int m_year{};
        int m_length{};
        double m_price{};
    };

    class SongCollection {
        std::vector<Song> songs;

    public:

        SongCollection(const std::string& fileName);

        void display(std::ostream& out) const;
        void sort(const std::string& type);
        void cleanAlbum();
        bool inCollection(const std::string& name) const;

        std::list<Song> getSongsForArtist(const std::string& name) const;

    };
    std::ostream& operator<<(std::ostream& out, const Song& song);
}
#endif
