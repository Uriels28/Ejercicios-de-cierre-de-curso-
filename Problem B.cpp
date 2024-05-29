#include <bits/stdc++.h>
using namespace std;

int n, w;
vector<string> ans;
int res = INT_MAX;

void backtrack(int week, int aislamiento, vector<string> &schedule) {
   if (week == w + 1) {
       if (aislamiento < res) {
           res = aislamiento;
           ans = schedule;
       }
       return;
   }

   for (int mask = 0; mask < (1 << n); mask++) {
       bool valid = true;
       int curr_aislamiento = 0;
       for (int i = 0; i < n; i++) {
           for (int j = i + 1; j < n; j++) {
               if ((mask & (1 << i)) && (mask & (1 << j))) {
                   int last_meet = -1;
                   for (int k = week - 1; k >= 0; k--) {
                       if (schedule[k][i] != schedule[k][j]) {
                           last_meet = k;
                           break;
                       }
                   }
                   curr_aislamiento = max(curr_aislamiento, week - last_meet);
               }
           }
       }

       string curr_schedule(n, '0');
       for (int i = 0; i < n; i++) {
           if (mask & (1 << i)) {
               curr_schedule[i] = '1';
           } else {
               curr_schedule[i] = '2';
           }
       }

       schedule.push_back(curr_schedule);
       backtrack(week + 1, max(aislamiento, curr_aislamiento), schedule);
       schedule.pop_back();
   }
}

int main() {
   cin >> n >> w;

   vector<string> schedule;
   backtrack(1, 0, schedule);

   if (res == INT_MAX) {
       cout << "infinito" << endl;
   } else {
       cout << res << endl;
       for (const string &s : ans) {
           cout << s << endl;
       }
   }

   return 0;
}
