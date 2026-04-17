#ifndef HISTORY_HPP
#define HISTORY_HPP

#include <string>
#include <vector>
#include <nlohmann/json.hpp> // Make sure to include the JSON library

struct download_history_entry_t {
    std::string url;           // The URL of the downloaded item
    std::string filename;      // The filename of the downloaded item
    std::string timestamp;     // The time of the download in ISO format

    // Function to serialize to JSON
    nlohmann::json to_json() const {
        return nlohmann::json{{"url", url}, {"filename", filename}, {"timestamp", timestamp}};
    }

    // Function to deserialize from JSON
    static download_history_entry_t from_json(const nlohmann::json& j) {
        download_history_entry_t entry;
        j.at("url").get_to(entry.url);
        j.at("filename").get_to(entry.filename);
        j.at("timestamp").get_to(entry.timestamp);
        return entry;
    }
};

struct download_history_manager_t {
    std::vector<download_history_entry_t> entries;

    // Function to add an entry
    void add_entry(const download_history_entry_t& entry) {
        entries.push_back(entry);
    }

    // Function to serialize the history to JSON
    nlohmann::json to_json() const {
        nlohmann::json j_entries = nlohmann::json::array();
        for (const auto& entry : entries) {
            j_entries.push_back(entry.to_json());
        }
        return j_entries;
    }

    // Function to deserialize from JSON
    static download_history_manager_t from_json(const nlohmann::json& j) {
        download_history_manager_t manager;
        for (const auto& entry_json : j) {
            manager.add_entry(download_history_entry_t::from_json(entry_json));
        }
        return manager;
    }
};

#endif // HISTORY_HPP
