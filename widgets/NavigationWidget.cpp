#include "NavigationWidget.h"
#include "../mainwindow.h"
#include "../util/ClickedButton.h"
#include "MainWidget.h"
#include "MapPointButton.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <utility>
#include <vector>
#include <map>
#include <cmath>
#include "Edge.h"
#include <queue>
#include "set"
#include "DSU.h"
#include <algorithm>
#include <functional>
#include "../util/NoticeDialog.h"
NavigationWidget::NavigationWidget(MainWindow* owner, QWidget* parent)
    : QWidget(parent), owner(owner)
{
    layout = new QVBoxLayout(this);
    layout->setContentsMargins(8, 8, 8, 8);
    layout->setSpacing(8);

    backButton = new ClickedButton("返回主界面", ClickedButton::textOnLight, ClickedButton::dangerRed, this);
    backButton->setHeight(40);
    backButton->setFontSize(14);
    layout->addWidget(backButton);
    connect(backButton, &QPushButton::clicked, this, &NavigationWidget::backButtonClicked);

    pipeButton = new ClickedButton("最优水管铺设", ClickedButton::textOnLight, ClickedButton::secondaryGray, this);
    pipeButton->setHeight(40);
    pipeButton->setFontSize(14);
    layout->addWidget(pipeButton);
    connect(pipeButton, &QPushButton::clicked, this, &NavigationWidget::pipeButtonClicked);

    navigationButton = new ClickedButton("路径导航", ClickedButton::textOnLight, ClickedButton::secondaryGray, this);
    navigationButton->setHeight(40);
    navigationButton->setFontSize(14);
    layout->addWidget(navigationButton);
    connect(navigationButton, &QPushButton::clicked, this, &NavigationWidget::navigationButtonClicked);

    infoButton = new ClickedButton("景点信息", ClickedButton::textOnLight, ClickedButton::secondaryGray, this);
    infoButton->setHeight(40);
    infoButton->setFontSize(14);
    layout->addWidget(infoButton);
    connect(infoButton, &QPushButton::clicked, this, &NavigationWidget::infoButtonClicked);

    dfsButton = new ClickedButton("遍历景点", ClickedButton::textOnLight, ClickedButton::secondaryGray, this);
    dfsButton->setHeight(40);
    dfsButton->setFontSize(14);
    layout->addWidget(dfsButton);
    connect(dfsButton, &QPushButton::clicked, this, &NavigationWidget::dfsButtonClicked);

    infoShowWidget = new QWidget(this);
    infoShowWidget->setMinimumHeight(600);
    infoShowWidget->setStyleSheet("QWidget { border: 1px solid gray; border-radius: 8px; background-color: white; }");
    infoLayout = new QVBoxLayout(infoShowWidget);
    infoLayout->setContentsMargins(4, 4, 4, 4);
    infoLayout->setSpacing(0);
    layout->addWidget(infoShowWidget);

    defaultLabel = new QLabel("请选择需要查看的路径点", infoShowWidget);
    defaultLabel->setAlignment(Qt::AlignCenter);
    defaultLabel->setStyleSheet("QLabel { border: none; color: lightgray; font-size: 14px; }");
    switchInfoShowWidget(defaultLabel);

    layout->addStretch(1);

    infoWidget = new InfoWidget(infoShowWidget);

    buttonColorUpdate();
}

void NavigationWidget::backButtonClicked()
{
    owner->displayPoints(owner->mapDataContainer);
    setFirstClickedButtonName("");
    setSecondClickedButtonName("");
    setClickedNum(0);
    if (owner) {
        owner->setMouseClickedType(0);
        owner->changeRightWidgetShow(owner->getMainWidget());
    }
}

void NavigationWidget::pipeButtonClicked()
{
    owner->displayPoints(owner->mapDataContainer);
    if (owner) {
        owner->setMouseClickedType(MainWindow::PIPE);
        buttonColorUpdate();
    }
    std::vector<MapPointButton*> indexToPoint(owner->getMapDataContainer()->pointButtonContainer.size()+1,nullptr);
    std::map<MapPointButton*,int>  pointToIndex;
    std::map<std::string,MapPointButton*> nameToPoint;
    DSU osu(owner->getMapDataContainer()->pointButtonContainer.size()+1);
    int index = 1;
    for (auto point : owner->getMapDataContainer()->pointButtonContainer) {
        indexToPoint[index] = point;
        pointToIndex[point] = index;
        nameToPoint[point->getName()] = point;
        index++;
    }
    

    struct EdgeInfo {
        double dis;
        int index1, index2;
        bool operator<(const EdgeInfo& other) const {
            return dis > other.dis;
        }
    };
    std::priority_queue<EdgeInfo> edges;
    for (auto edge: owner->getMapDataContainer()->edgeContainer) {
        std::string name1 = edge->getFirstPointButton()->getName();
        std::string name2 = edge->getSecondPointButton()->getName();
        int index1 = pointToIndex[nameToPoint[name1]];
        int index2 = pointToIndex[nameToPoint[name2]];
        int x1 = edge->getFirstPointButton()->getX();
        int y1 = edge->getFirstPointButton()->getY();
        int x2 = edge->getSecondPointButton()->getX();
        int y2 = edge->getSecondPointButton()->getY();
        double dis = sqrt((double)(x1-x2)*(x1-x2)+(double)(y1-y2)*(y1-y2));
        edges.push({dis,index1,index2});
    }
    std::set<std::pair<int,int>> pipeEdges;
    while (!edges.empty()) {
        EdgeInfo e = edges.top();
        edges.pop();
        if (osu.findParent(e.index1) != osu.findParent(e.index2)) {
            osu.merge(e.index1,e.index2);
            pipeEdges.insert({e.index1,e.index2});
        }
    }

    for (auto edge: owner->getMapDataContainer()->edgeContainer) {
        int index1 = pointToIndex[edge->getFirstPointButton()];
        int index2 = pointToIndex[edge->getSecondPointButton()];
        if (pipeEdges.find({index1,index2}) != pipeEdges.end() || pipeEdges.find({index2,index1}) != pipeEdges.end()) {
            edge->setType(1);
        } else {
            edge->setType(-1);
        }
    }
    owner->displayPoints(owner->mapDataContainer);
    for (auto edge: owner->getMapDataContainer()->edgeContainer) {
        edge->setType(0);
    }
}

void NavigationWidget::navigationButtonClicked()
{
    owner->displayPoints(owner->mapDataContainer);
    setClickedNum(0);
    setFirstClickedButtonName("");
    setSecondClickedButtonName("");
    if (owner) {
        owner->setMouseClickedType(MainWindow::NAVIGATION);
        buttonColorUpdate();
    }
}

void NavigationWidget::infoButtonClicked()
{
    // TODO 稍后完成
    if (owner) {
        owner->setMouseClickedType(MainWindow::INFO);
        buttonColorUpdate();
    }
}

void NavigationWidget::dfsButtonClicked()
{
    owner->displayPoints(owner->mapDataContainer);
    setClickedNum(0);
    setFirstClickedButtonName("");
    setSecondClickedButtonName("");
    if (owner) {
        owner->setMouseClickedType(MainWindow::DFS);
        buttonColorUpdate();
    }
}

void NavigationWidget::switchInfoShowWidget(QWidget* infoWidget)
{
    if (!infoLayout) return;

    QLayoutItem* item;
    while ((item = infoLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            item->widget()->hide();
            if (item->widget() != defaultLabel && item->widget() != this->infoWidget) {
                item->widget()->deleteLater();
            }
        }
        delete item;
    }

    if (infoWidget) {
        infoLayout->addWidget(infoWidget);
        infoWidget->show();
    }
}

void NavigationWidget::buttonColorUpdate()
{
    if (!owner) return;
    int t = owner->getMouseClickedType();
    
    if (t == MainWindow::PIPE) {
        pipeButton->setColors(ClickedButton::textOnLight, ClickedButton::successGreen);
    } else {
        pipeButton->setColors(ClickedButton::textOnLight, ClickedButton::secondaryGray);
    }

    if (t == MainWindow::NAVIGATION) {
        if (clickedButtonNum == 0) {
            navigationButton->setColors(ClickedButton::textOnLight, ClickedButton::successGreen);
        } else if (clickedButtonNum == 1) {
            navigationButton->setColors(ClickedButton::textOnLight, ClickedButton::warningAmber);
        } else {
             navigationButton->setColors(ClickedButton::textOnLight, ClickedButton::secondaryGray);
        }
    } else {
        navigationButton->setColors(ClickedButton::textOnLight, ClickedButton::secondaryGray);
    }

    if (t == MainWindow::INFO) {
        infoButton->setColors(ClickedButton::textOnLight, ClickedButton::successGreen);
    } else {
        infoButton->setColors(ClickedButton::textOnLight, ClickedButton::secondaryGray);
    }

    if (t == MainWindow::DFS) {
        dfsButton->setColors(ClickedButton::textOnLight, ClickedButton::successGreen);
    } else {
        dfsButton->setColors(ClickedButton::textOnLight, ClickedButton::secondaryGray);
    }
}

void NavigationWidget::setFirstClickedButtonName(std::string name) {
    firstClickedButtonName = name;
}

void NavigationWidget::setSecondClickedButtonName(std::string name) {
    secondClickedButtonName = name;
}

void NavigationWidget::setClickedNum(int num) {
    clickedButtonNum = num;
}

std::string NavigationWidget::getFirstClickedButtonName() const {
    return firstClickedButtonName;
}

std::string NavigationWidget::getSecondClickedButtonName() const {
    return secondClickedButtonName;
}

int NavigationWidget::getClickedNum() const {
    return clickedButtonNum;
}

void NavigationWidget::dij(std::string start, std::string end) {
    auto* container = owner->getMapDataContainer();
    if (!container) return;
    
    std::map<std::string, int> nameToIndex;
    int n = container->pointButtonContainer.size();
    std::vector<MapPointButton*> indexToPoint(n + 1, nullptr);
    
    int index = 1;
    for (auto pointButton : container->pointButtonContainer) {
        nameToIndex[pointButton->getName()] = index;
        indexToPoint[index++] = pointButton;
    }
    
    std::vector<std::vector<double>> mat(n + 1, std::vector<double>(n + 1, 1e18));
    for (auto edge : container->edgeContainer) {
        if (nameToIndex.find(edge->getFirstPointButton()->getName()) == nameToIndex.end() ||
            nameToIndex.find(edge->getSecondPointButton()->getName()) == nameToIndex.end()) continue;

        int index1 = nameToIndex[edge->getFirstPointButton()->getName()];
        int index2 = nameToIndex[edge->getSecondPointButton()->getName()];
        int x1 = edge->getFirstPointButton()->getX();
        int y1 = edge->getFirstPointButton()->getY();
        int x2 = edge->getSecondPointButton()->getX();
        int y2 = edge->getSecondPointButton()->getY();
        double len = sqrt((double)(x1 - x2) * (x1 - x2) + (double)(y1 - y2) * (y1 - y2));
        mat[index1][index2] = len;
        mat[index2][index1] = len;
    }

    std::vector<bool> visited(n + 1, false);
    std::vector<double> dis(n + 1, 1e18);
    struct node {
        double dis;
        int u;
        bool operator>(const node& a) const { return dis > a.dis; }
    };
    std::priority_queue<node, std::vector<node>, std::greater<node>> q;
    if (nameToIndex.find(start) == nameToIndex.end() || nameToIndex.find(end) == nameToIndex.end()) return;
    int startIndex = nameToIndex[start];
    int endIndex = nameToIndex[end];
    dis[startIndex] = 0;
    q.push({0, startIndex});
    std::vector<std::vector<int>> path(n + 1, std::vector<int>());
    path[startIndex].push_back(startIndex);
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (visited[u]) continue;
        visited[u] = true;
        if (u == endIndex) break;
        for (int v = 1; v <= n; v++) {
             if (mat[u][v] < 1e17) {
                if (dis[v] > dis[u] + mat[u][v]) {
                    dis[v] = dis[u] + mat[u][v];
                    q.push({dis[v], v});
                    path[v] = path[u];
                    path[v].push_back(v);
                }
             }
        }
    }

    std::set<std::pair<int, int>> pathEdges;
    if (!path[endIndex].empty()) {
        for (int i = 0; i < path[endIndex].size() - 1; i++) {
            pathEdges.insert({path[endIndex][i], path[endIndex][i+1]});
        }
    }

    for (auto edge : container->edgeContainer) {
        if (nameToIndex.find(edge->getFirstPointButton()->getName()) == nameToIndex.end() ||
            nameToIndex.find(edge->getSecondPointButton()->getName()) == nameToIndex.end()) continue;

        int index1 = nameToIndex[edge->getFirstPointButton()->getName()];
        int index2 = nameToIndex[edge->getSecondPointButton()->getName()];
        
        if (pathEdges.find({index1, index2}) != pathEdges.end() || 
            pathEdges.find({index2, index1}) != pathEdges.end()) {
            edge->setType(2);
        } else {
            edge->setType(-1);
        }
    }
    owner->displayPoints(owner->mapDataContainer);
    
    for (auto edge : owner->getMapDataContainer()->edgeContainer) {
        edge->setType(0);
    }
}

QLabel* NavigationWidget::getDefaultLabel() const { return defaultLabel; }
void NavigationWidget::setDefaultLabel(QLabel* label) { defaultLabel = label; }

void NavigationWidget::dfs(std::string start) {
    auto* container = owner->getMapDataContainer();
    if (!container) return;
    
    std::map<std::string, int> nameToIndex;
    int n = container->pointButtonContainer.size();
    int index = 1;
    for (auto pointButton : container->pointButtonContainer) {
        nameToIndex[pointButton->getName()] = index;
        index++;
    }

    std::vector<std::string> scenicSpotNames;
    for (auto point : container->pointButtonContainer) {
        if (point->getType() == 2) {
            scenicSpotNames.push_back(point->getName());
        }
    }
    if (scenicSpotNames.empty()) return;

    struct AdjNode {
        int to;
        double weight;
        Edge* edge;
    };
    std::vector<std::vector<AdjNode>> adj(n + 1);
    for (auto edge : container->edgeContainer) {
        std::string uName = edge->getFirstPointButton()->getName();
        std::string vName = edge->getSecondPointButton()->getName();
        if (nameToIndex.find(uName) == nameToIndex.end() || nameToIndex.find(vName) == nameToIndex.end()) continue;
        
        int u = nameToIndex[uName];
        int v = nameToIndex[vName];
        
        int x1 = edge->getFirstPointButton()->getX();
        int y1 = edge->getFirstPointButton()->getY();
        int x2 = edge->getSecondPointButton()->getX();
        int y2 = edge->getSecondPointButton()->getY();
        double w = std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
        
        adj[u].push_back({v, w, edge});
        adj[v].push_back({u, w, edge});
    }

    std::map<std::pair<std::string,std::string>, std::vector<Edge*>> scenePaths;
    int k = scenicSpotNames.size();
    std::vector<std::vector<double>> sceneMat(k, std::vector<double>(k, 1e18));
    std::map<std::string, int> sceneNameToIndex;
    for(int i = 0; i < k; ++i) sceneNameToIndex[scenicSpotNames[i]] = i;

    //对可达的两个景点DIJ，并构建最短路径
    for(int i = 0; i < k; ++i) {
        int startNode = nameToIndex[scenicSpotNames[i]];
        std::vector<double> dist(n + 1, 1e18);
        std::vector<int> parent(n + 1, 0);
        std::vector<Edge*> parentEdge(n + 1, nullptr);
        
        dist[startNode] = 0;
        std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;
        pq.push({0, startNode});
        
        while(!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue;
            
            for(auto& e : adj[u]) {
                if (dist[u] + e.weight < dist[e.to]) {
                    dist[e.to] = dist[u] + e.weight;
                    parent[e.to] = u;
                    parentEdge[e.to] = e.edge;
                    pq.push({dist[e.to], e.to});
                }
            }
        }
        
        for(int j = 0; j < k; ++j) {
            if (i == j) {
                sceneMat[i][j] = 0;
                continue;
            }
            int endNode = nameToIndex[scenicSpotNames[j]];
            if (dist[endNode] < 1e17) {
                sceneMat[i][j] = dist[endNode];
                if (scenicSpotNames[i] < scenicSpotNames[j]) {
                    std::vector<Edge*> path;
                    int curr = endNode;
                    while(curr != startNode) {
                        path.push_back(parentEdge[curr]);
                        curr = parent[curr];
                    }
                    std::reverse(path.begin(), path.end());
                    scenePaths[{scenicSpotNames[i], scenicSpotNames[j]}] = path;
                }
            }
        }
    }

    if (sceneNameToIndex.find(start) == sceneNameToIndex.end()) return;
    int startSceneIdx = sceneNameToIndex[start];
    
    std::vector<Edge*> allScenePath;
    std::vector<int> pathIndices;
    std::vector<bool> visited(k, false);

    std::function<bool(int)> dfsHelper = [&](int u) {
        pathIndices.push_back(u);
        visited[u] = true;

        if (pathIndices.size() == k) return true;

        for (int v = 0; v < k; ++v) {
            if (!visited[v] && sceneMat[u][v] < 1e17) {
                if (dfsHelper(v)) return true;
            }
        }

        visited[u] = false;
        pathIndices.pop_back();
        return false;
    };

    if (dfsHelper(startSceneIdx)) {
        for (size_t i = 0; i < pathIndices.size() - 1; ++i) {
            std::string n1 = scenicSpotNames[pathIndices[i]];
            std::string n2 = scenicSpotNames[pathIndices[i+1]];
            std::pair<std::string, std::string> key;
            if (n1 < n2) key = {n1, n2};
            else key = {n2, n1};
            
            if (scenePaths.count(key)) {
                const auto& edges = scenePaths[key];
                allScenePath.insert(allScenePath.end(), edges.begin(), edges.end());
            }
        }
        if (owner && owner->leftWidget) {
            owner->leftWidget->drawPathWithGradient(container, allScenePath);
        }
    } else {
        NoticeDialog* notice = new NoticeDialog("提示", "无法到达全部景点");
        notice->exec();
    }
}
