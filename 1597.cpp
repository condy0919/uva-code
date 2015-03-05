#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <utility>
#include <cctype>
#include <memory>
#include <sstream>

using namespace std;

class TextQuery {
public:
    void build_map() {
        string line;
        while (getline(cin, line), line != "**********") {
            string s;
            transform(line.begin(), line.end(), back_inserter(s), [](char c) {
                if (isalpha(c))
                    return tolower(c);
                return static_cast<int>(' ');
            });
            istringstream iss(s);
            while (iss >> s) {
                if (!isalpha(s.back()))
                    s.pop_back();
                word_map[s].insert(lines_of_text.size());
            }
            lines_of_text.push_back(line);
        }
    }

    shared_ptr<set<int>> run_query(const string& s) const {
        auto iter = word_map.find(s);
        if (iter == word_map.end())
            return make_shared<set<int>>();
        return make_shared<set<int>>(iter->second);
    }

    shared_ptr<set<int>> whole_line_no() const {
        set<int> _set;
        for (int i = 0; i < lines_of_text.size(); ++i)
            _set.insert(i);
        return make_shared<set<int>>(_set);
    }

    string text_line(int idx) const { return lines_of_text[idx]; }

private:
    vector<string> lines_of_text;
    map<string, set<int>> word_map;
};

class Query;

class QueryBase {
    friend class Query;

public:
    virtual ~QueryBase() {}

private:
    virtual shared_ptr<set<int>> eval(const TextQuery&) const = 0;
};

class WordQuery : public QueryBase {
    friend class Query;

    WordQuery(string s) : query_word(move(s)) {}

    virtual shared_ptr<set<int>> eval(const TextQuery& t) const {
        return t.run_query(query_word);
    }

    string query_word;
};

class Query {
    friend Query operator~(const Query&);
    friend Query operator&(const Query&, const Query&);
    friend Query operator|(const Query&, const Query&);

public:
    Query(string s) : q(new WordQuery(s)) {}
    Query() = default;

    shared_ptr<set<int>> eval(const TextQuery& t) const { return q->eval(t); }

private:
    shared_ptr<QueryBase> q;
    Query(QueryBase* query) : q(query) {}
};

class NotQuery : public QueryBase {
    friend Query operator~(const Query&);

    NotQuery(Query q) : query(q) {}

    virtual shared_ptr<set<int>> eval(const TextQuery& t) const {
        shared_ptr<set<int>> ans = query.eval(t);
        if (ans->empty())
            return t.whole_line_no();
        return make_shared<set<int>>();
    }

    const Query query;
};

class BinaryQuery : public QueryBase {
protected:
    BinaryQuery(Query l, Query r, string op) : left(l), right(r), oper(op) {}

    Query left, right;
    const string oper;
};

class AndQuery : public BinaryQuery {
    friend Query operator&(const Query&, const Query&);

    AndQuery(Query l, Query r) : BinaryQuery(l, r, "&") {}

    shared_ptr<set<int>> eval(const TextQuery& t) const {
        shared_ptr<set<int>> l = left.eval(t), r = right.eval(t);
        if (l->empty() || r->empty())
            return make_shared<set<int>>();
        l->insert(r->begin(), r->end());
        return l;
    }
};

class OrQuery : public BinaryQuery {
    friend Query operator|(const Query&, const Query&);

    OrQuery(Query l, Query r) : BinaryQuery(l, r, "|") {}

    shared_ptr<set<int>> eval(const TextQuery& t) const {
        shared_ptr<set<int>> l = left.eval(t), r = right.eval(t);
        l->insert(r->begin(), r->end());
        return l;
    }
};

Query operator&(const Query& lhs, const Query& rhs) {
    return new AndQuery(lhs, rhs);
}

Query operator|(const Query& lhs, const Query& rhs) {
    return new OrQuery(lhs, rhs);
}

Query operator~(const Query& q) { return new NotQuery(q); }

vector<string> split(const string& s) {
    istringstream iss(s);
    vector<string> v;
    string _s;
    while (iss >> _s)
        v.push_back(_s);
    return v;
}

int main() {
    ios::sync_with_stdio(false);

    int n;
    (cin >> n).ignore();
    vector<TextQuery> articles(n);
    for (auto& i : articles)
        i.build_map();

    string line;
    Query q;
    (cin >> n).ignore();
    while (n-- > 0) {
        getline(cin, line);
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        switch (count(line.begin(), line.end(), ' ')) {
        case 0:  // WordQuery
            q = Query(line);
            break;
        case 1:  // NotQuery
            q = ~Query(split(line)[1]);
            break;
        case 2:  // AndQuery or OrQuery
            {
                vector<string> sp = split(line);
                if (sp[1] == "and")
                    q = Query(sp[0]) & Query(sp[2]);
                else
                    q = Query(sp[0]) | Query(sp[2]);
            }
            break;
        default:
            throw runtime_error("");
        }

        auto fn = [first = true](const set<int>& ls, const TextQuery& t) mutable {
            if (first)
                first = false;
            else
                cout << "----------\n";
            for (const auto& i : ls)
                cout << t.text_line(i) << '\n';
        };
        bool empty = true;
        for (auto& i : articles) {
            shared_ptr<set<int>> ls = q.eval(i);
            if (ls->empty())
                continue;
            fn(*ls, i);
            empty = false;
        }
        if (empty)
            cout << "Sorry, I found nothing.\n";
        cout << "==========\n";
    }

    return 0;
}
