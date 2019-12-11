#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct team {
    string name;
    float time;
    int age;
};

void readTeam(team Team[], int teamSize, const char filename[]);
int findTeamSize(const char filename[]);
void joinMembers(team Team1[], int team1Size, team Team2[], int team2Size, team JoinedMembers[], int joinedMembersCount);
bool compareMembers(team Member1, team Member2);
void getTopMembers(team ATeam[], int topCount, team JoinedMembers[], int joinedMembersCount);
void writeResults(team ATeam[], int topCount, const char filename[]);

int main()
{

    const char team1[] = "duom1.txt",
               team2[] = "duom2.txt",
               results[] = "rez.txt";

    int team1Size = findTeamSize(team1),
        team2Size = findTeamSize(team2),
        allMembersCount = team1Size + team2Size,
        topCount = 5;

    team Team1[team1Size],
         Team2[team2Size],
         AllMembers[allMembersCount],
         ATeam[topCount];

    readTeam(Team1, team1Size, team1);
    readTeam(Team2, team2Size, team2);
    joinMembers(Team1, team1Size, Team2, team2Size, AllMembers, allMembersCount);
    getTopMembers(ATeam, topCount, AllMembers, allMembersCount);
    writeResults(ATeam, topCount, results);

}

void readTeam(team Team[], int teamSize, const char filename[])
{

    ifstream in(filename);

    for(int i = 0; i < teamSize; i++) {
        in >> Team[i].name >> Team[i].time >> Team[i].age;
    }

    in.close();
}

int findTeamSize(const char filename[])
{
    ifstream in(filename);
    int n = 0;
    string line;

    while(!in.eof()) {
        getline(in, line);
        n++;
    }
    in.close();

    return n;
}

void joinMembers(team Team1[], int team1Size, team Team2[], int team2Size, team JoinedMembers[], int joinedMembersCount)
{
    int j = 0;
    for(int i = 0; i < team1Size; i++) {
        JoinedMembers[j].name = Team1[i].name;
        JoinedMembers[j].time = Team1[i].time;
        JoinedMembers[j].age = Team1[i].age;
        j++;
    }

    for(int i = 0; i < team2Size; i++) {
        JoinedMembers[j].name = Team2[i].name;
        JoinedMembers[j].time = Team2[i].time;
        JoinedMembers[j].age = Team2[i].age;
        j++;
    }
}

bool compareMembers(team Member1, team Member2)
{
    bool member1IsBetter = false;

    if (Member1.time < Member2.time) {
        member1IsBetter = true;
    } else if (Member1.time == Member2.time) {
        if (Member1.age < Member2.age) {
            member1IsBetter = true;
        }
    }

    return member1IsBetter;
}

void getTopMembers(team ATeam[], int topCount, team JoinedMembers[], int joinedMembersCount)
{
    sort(JoinedMembers, JoinedMembers + joinedMembersCount, compareMembers) ;
    for(int i = 0; i < topCount; i++) {
        ATeam[i].name = JoinedMembers[i].name;
        ATeam[i].time = JoinedMembers[i].time;
        ATeam[i].age = JoinedMembers[i].age;
    }
}

void writeResults(team ATeam[], int topCount, const char filename[])
{
    ofstream out(filename);

    out << "Olimpines komandos nariai\n";
    out << "###########################\n";
    out << "Vardas / Laikas / Amzius \n";
    for(int i = 0; i < topCount; i++) {
        out << i + 1 << ". "  << ATeam[i].name << " / " << ATeam[i].time << "s / " << ATeam[i].age << "m.\n";
    }

    out.close();
}