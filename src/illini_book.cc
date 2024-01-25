#include "illini_book.hpp"
#include <fstream>
#include <queue>
// Your code here!

IlliniBook::IlliniBook(const std::string& people_fpath, const std::string& relations_fpath) {
    std::ifstream uins{people_fpath};
    std::ifstream relationships(relations_fpath);
    std::string line;
    while(std::getline(uins, line)) {
        graph_[std::stoi(line)] = {};
        line = "";
    }
    while (std::getline(relationships, line)) {
        std::vector<std::string> relationship = utilities::Split(line, ',');
        graph_[std::stoi(relationship.at(0))][std::stoi(relationship.at(1))] = relationship.at(2);
        graph_[std::stoi(relationship.at(1))][std::stoi(relationship.at(0))] = relationship.at(2);
        line = "";
    }
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
    std::set<int> visited;
    std::queue<int> queue;
    queue.push(uin_1);
    while (!queue.empty()) {
        int curr = queue.front();
        if (curr == uin_2) {
            return true;
        }
        visited.insert(curr);
        for (auto it = graph_.at(curr).begin(); it != graph_.at(curr).end(); it++) {
            if (!visited.contains(it->first)) {
                queue.push(it->first);
            }
        }
        queue.pop();
    }
    return false;
}

bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string &relationship) const {
    std::set<int> visited;
    std::queue<int> queue;
    queue.push(uin_1);
    while (!queue.empty()) {
        int curr = queue.front();
        visited.insert(curr);
        for (auto it = graph_.at(curr).begin(); it != graph_.at(curr).end(); it++) {
            if (!visited.contains(it->first) && it -> second == relationship) {
                if (it -> first == uin_2) {
                    return true;
                }
                queue.push(it->first);
            }
        }
        queue.pop();
    }
    return false;
}


//2
int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  std::set<int> visited;
  std::queue<std::pair<int, int>> queue;
  queue.push({uin_1,0});

  while (!queue.empty()) {
    std::pair packet = queue.front();
    int curr = packet.first;
    int dist = packet.second+1;
    if (curr == uin_2) {
        return dist-1;
    }
    visited.insert(curr);
    for (auto it = graph_.at(curr).begin(); it != graph_.at(curr).end(); it++) {
        if (!visited.contains(it->first)) {
            queue.push({it->first, dist});
        }
    }
    queue.pop();
  }
  return -1;
}

//3
int IlliniBook::GetRelated(int uin_1, int uin_2, const std::string &relationship) const {
  std::set<int> visited;
  std::queue<std::pair<int, int>> queue;
  queue.push({uin_1,0});

  while (!queue.empty()) {
    std::pair packet = queue.front();
    int curr = packet.first;
    int dist = packet.second+1;
    visited.insert(curr);
    for (auto it = graph_.at(curr).begin(); it != graph_.at(curr).end(); it++) {
        if (!visited.contains(it->first) && it -> second == relationship) {
            if (it -> first == uin_2) {
                return dist;
            }
            queue.push({it->first, dist});
        }
    }
    queue.pop();
  }
  return -1;
}


std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
    std::set<int> visited;
    std::set<int> deep_visited;
    std::set<int> matches_set;

    std::vector<int> matches;

    std::queue<std::pair<int,int>> queue;
    queue.push({uin, 0});
    while (!queue.empty()) {
        std::pair<int,int> packet = queue.front();
        int curr = packet.first;
        int dist = packet.second + 1;
        deep_visited.insert(curr);
        for (auto it = graph_.at(curr).begin(); it != graph_.at(curr).end(); it++) {
            if (!deep_visited.contains(it->first)) {
                if (dist+1 == n && !visited.contains(it->first) && !matches_set.contains(it->first)) {
                 matches_set.insert(it->first);
                 matches.push_back(it->first);
                } else {
                    visited.insert(it->first);
                    queue.push({it->first, dist});
                }
            }
        }
        queue.pop();
    }
    return matches;
}

//2
size_t IlliniBook::CountGroups() const {
  std::set<int> visited;
  size_t count = 0;
  
  for (auto const& curr_edge : graph_) {
    if (!visited.contains(curr_edge.first)) {
      std::queue<int> queue;
      queue.push(curr_edge.first);
      while (!queue.empty()) {
        int curr = queue.front();
        visited.insert(curr);
        for (auto it = graph_.at(curr).begin(); it != graph_.at(curr).end(); it++) {
            if (!visited.contains(it->first)) {
                queue.push(it->first);
            }
        }
        queue.pop();
      }
      count++;
    }
  }
  return count;
}


size_t IlliniBook::CountGroups(const std::string &relationship) const {
  std::set<int> visited;
  size_t count = 0;
  
  for (auto const& curr_edge : graph_) {
    if (!visited.contains(curr_edge.first)) {
      std::queue<int> queue;
      queue.push(curr_edge.first);
      while (!queue.empty()) {
        int curr = queue.front();
        visited.insert(curr);
        for (auto it = graph_.at(curr).begin(); it != graph_.at(curr).end(); it++) {
            if (!visited.contains(it->first) && it->second == relationship) {
                queue.push(it->first);
            }
        }
        queue.pop();
      }
      count++;
    }
  }
  return count;
}



size_t IlliniBook::CountGroups(const std::vector<std::string> &relationships) const {
  std::set<int> visited;
  size_t count = 0;
  
  for (auto const& curr_edge : graph_) {
    if (!visited.contains(curr_edge.first)) {
      std::queue<int> queue;
      queue.push(curr_edge.first);
      while (!queue.empty()) {
        int curr = queue.front();
        visited.insert(curr);
        for (auto it = graph_.at(curr).begin(); it != graph_.at(curr).end(); it++) {
            for (const std::string& relation : relationships) {
                if (!visited.contains(it->first) && it->second == relation) {
                    queue.push(it->first);
                    break;
                }
            }
        }
        queue.pop();
      }
      count++;
    }
  }
  return count;
}