#include <cstdio>
#include <iostream>
#include <stack>
#include <map>
#include <string>

typedef long long ll;

using namespace std;

template <class T>
inline T poll(stack<T>& s) { T e = s.top(); s.pop(); return e; }

ll eval(string expr, map<char, int> prec) {
  stack<char> ops; stack<ll> args;
  expr = "(" + expr + ")";

  auto applyOp = [&]() {
    switch(poll(ops)) {
      case '+': args.push(poll(args) + poll(args)); break;
      case '*': args.push(poll(args) * poll(args)); break;
    }
  };
  for(char ch : expr) {
    switch(ch) {
      case ' ': break;
      case '(': ops.push(ch); break;
      case ')':
        while(ops.top() != '(') applyOp();
        ops.pop();
        break;
      default:
        if(ch >= '0' && ch <= '9') args.push(ch - '0');
        else {
          while(ops.top() != '(' && prec[ch] >= prec[ops.top()]) applyOp();
          ops.push(ch);
        }
    }
  }
  return args.top();
}

int main() {
  ll res1 = 0, res2 = 0;
  string line;
  while(getline(cin, line)) {
    res1 += eval(line, {{'+', 1}, {'*', 1}});
    res2 += eval(line, {{'+', 1}, {'*', 2}});
  }
  printf("%lld %lld\n", res1, res2);
  return 0;
}
