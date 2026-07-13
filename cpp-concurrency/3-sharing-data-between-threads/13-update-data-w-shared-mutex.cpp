#include <map>
#include <mutex>
#include <shared_mutex>
#include <string>

class dns_entry {
  public:
    dns_entry() {}
    dns_entry(std::string const &name) : name_(name) {}
    std::string name_;
};

class dns_cache {
    std::map<std::string, dns_entry> entries;
    mutable std::shared_mutex entry_mutex;
    // shared_mutex = SWMR

  public:
    // many threads can read at same time
    dns_entry find_entry(std::string const &domain) const {
        std::shared_lock<std::shared_mutex> lk(entry_mutex);
        std::map<std::string, dns_entry>::const_iterator const it = entries.find(domain);
        return (it == entries.end()) ? dns_entry() : it->second;
    }

    // only one thread can write at a time
    void update_or_add_entry(std::string const &domain, dns_entry const &dns_details) {
        std::lock_guard<std::shared_mutex> lk(entry_mutex);
        entries[domain] = dns_details;
    }
};