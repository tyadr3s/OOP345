#include "SongCollection.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <numeric>
#include <sstream>
#include <stdexcept>

namespace seneca{
    std::string trim(std::string str){
        while (!str.empty() && str[0] == ' ') {
            str.erase(0, 1);
        }
        while (!str.empty() && str.back() == ' ') {
            str.pop_back();
        }
        return str;
    }

    SongCollection::SongCollection(const std::string& fileName) {
        std::ifstream file(fileName);
        if (!file) {
            throw std::runtime_error("Cannot open file");
        }
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            Song song;

            song.m_title = trim(line.substr(0, 25));
            song.m_artist = trim(line.substr(25, 25));
            song.m_album = trim(line.substr(50, 25));

            std::string year = trim(line.substr(75, 5));
            if (!year.empty()) {
                song.m_year = std::stoi(year);
            }

            song.m_length = std::stoi(trim(line.substr(80, 5)));
            song.m_price = std::stod(trim(line.substr(85, 5)));

            songs.push_back(song);
        }
    }

    void SongCollection::display(std::ostream& out) const{
        std::for_each(songs.begin(), songs.end(),  [&out](const Song& s) {
          out << s << '\n';
        });

        int total = std::accumulate(songs.begin(), songs.end(), 0,[](int sum, const Song& s) {
          return sum + s.m_length;
        });

        int hours = total / 3600;
        int mins = (total % 3600) / 60;
        int secs = total % 60;

        std::ostringstream time;

        time << hours << ':' << std::setfill('0') << std::setw(2) << mins << ':' << std::setw(2) << secs;

        out << std::string(88, '-') << '\n';

        out << "| " << std::right << std::setw(84) << ("Total Listening Time: " + time.str()) << " |\n";
    }

    void SongCollection::sort(const std::string& type) {
        std::stable_sort(songs.begin(), songs.end(),
            [type](const Song& a, const Song& b) {
                if (type == "title") {
                    return a.m_title < b.m_title;
                }
                if (type == "album") {
                    return a.m_album < b.m_album;
                }
                return a.m_length < b.m_length;
            });
    }

    void SongCollection::cleanAlbum() {
        std::transform(songs.begin(), songs.end(), songs.begin(), [](Song s) {
                if (s.m_album == "[None]") {
                    s.m_album = "";
                }
                return s;
            });
    }

    bool SongCollection::inCollection(const std::string& name) const {
        return std::any_of(songs.begin(), songs.end(), [name](const Song& s) {
                return s.m_artist == name;
            });
    }

    std::list<Song> SongCollection::getSongsForArtist(const std::string& name) const {
        std::list<Song> result;

        std::copy_if(songs.begin(), songs.end(), std::back_inserter(result), [name](const Song& s) {
                return s.m_artist == name;
            });

        return result;
    }

    std::ostream& operator<<(std::ostream& out, const Song& s) {
        out << "| " << std::left << std::setw(20) << s.m_title << " | " << std::setw(15) << s.m_artist << " | " << std::setw(20) << s.m_album << " | " << std::right << std::setw(6);
        if (s.m_year == 0) {
            out << "";
        } else {
            out << s.m_year;
        }
        out << " | " << s.m_length / 60 << ':' << std::setfill('0') << std::setw(2) << s.m_length % 60 << std::setfill(' ') << " | " << std::fixed << std::setprecision(2) << s.m_price << " |";
        return out;
    }
}
