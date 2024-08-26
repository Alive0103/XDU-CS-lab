#include <iostream>
 
#include "Astar.h"
 
bool InPath(const int &row, const int &col, const std::list<Point *> &path) {
  for (const auto &p : path) {
    if (row == (p->x) && col == p->y) {
      return true;
    }
  }
  return false;
}
 
int main() {
  //初始化地图，用二维矩阵代表地图，1表示障碍物，0表示可通
  std::vector<std::vector<int>> map = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                       {1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1},
                                       {1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
                                       {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1},
                                       {1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
                                       {1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
                                       {1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                                       {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
  Astar astar;
  astar.InitAstar(map);
 
  //设置起始和结束点
  Point start(1, 1);
  Point end(6, 10);
 
  // A*算法找寻路径
  std::list<Point *> path = astar.GetPath(start, end, false);
 
  // 打印结果
  for (auto &p : path) {
    std::cout << "(" << p->x << "," << p->y << ") ";
  }
  std::cout << "\n";
 
  for (int row = 0; row < map.size(); ++row) {
    for (int col = 0; col < map[0].size(); ++col) {
      if (InPath(row, col, path)) {
        if (map[row][col] != 0) {
          std::cout << "e ";
        } else {
          std::cout << "* ";
        }
      } else {
        std::cout << map[row][col] << " ";
      }
    }
    std::cout << "\n";
  }
  return 0;
}
