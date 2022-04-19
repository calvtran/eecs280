#include <map>
#include <iostream>
#include <fstream>
#include <set>
#include "csvstream.h"
#include <string>
#include <vector>
#include <cmath>
using namespace std;

using numword = std::map<string, int>;

class classifier {
private:
    int num_posts;
    set<string> uniqwords;
    set<string> uniqtags;
    vector<string> tags;
    vector<string> posts;
    vector<set<string>> mapost;
    numword num_posts_with_tag;
    numword num_post_per_word;
    map<pair<string,string>, int> num_post_word_by_label;
public:
    int get_num_posts()
    {
        return num_posts;
    }
    int get_num_uniq()
    {
        return uniqwords.size();
    }
    void getData(csvstream& data_in)
    {
        num_posts = 0;
        map<string, string> temp;
        for(int i = 0; data_in>>temp; i++)
        {
            tags.push_back(temp["tag"]);
            uniqtags.insert(temp["tag"]);
            posts.push_back(temp["content"]);
            mapost.push_back(splitwords(temp["content"]));
            num_posts++;
        }
        grabwords();
    }
    string getTag(const int &pos)
    {
        return tags[pos];
    }
    string getPost(const int& pos)
    {
        return posts[pos];
    }
    void calculate_count()
    {
        for (set<string>::iterator it=uniqtags.begin(); it!=uniqtags.end(); it++)
        {
            int count=0;
            for (int j = 0; j < num_posts; j++)
                if (tags[j] == *it)
                    count++;
            num_posts_with_tag[*it] = count;
        }
        for (set<string>::iterator it = uniqwords.begin(); it != uniqwords.end(); it++)
        {
            int count = 0;
            for (int i = 0; i < num_posts; i++)
            {
                if (mapost[i].find(*it) != mapost[i].end())
                    count++;
            }
            num_post_per_word[*it] = count;
        }
        calculate_count_given();
    }

    void getLabelProbs(classifier& in, vector<map<string,double>>& probability)
    {
        for (int i = 0; i < num_posts; i++)
        {
            map<string, double> temp;
            for (auto label = in.uniqtags.begin(); label != in.uniqtags.end(); label++)
            {
                double prob = log(in.num_posts_with_tag[*label]/
                    static_cast<double>(in.num_posts));
                for (auto j = mapost[i].begin(); j != mapost[i].end(); j++)
                {
                    int c = in.num_post_word_by_label[{*label, * j}];
                    if(c>0)
                        prob += log(c / static_cast<double>
                            (in.num_posts_with_tag[*label]));
                    else
                    {
                        c = in.num_post_per_word[*j];
                        if (c > 0)
                            prob += log(c / static_cast<double>(in.num_posts));
                        else
                            prob += log(1 / static_cast<double>(in.num_posts));
                    }
                }
                temp[*label] = prob;
            }
            probability.push_back(temp);
        }
    }

    void debugOption(ostream& os)
    {
        os << "training data:\n";
        for (int i = 0; i < num_posts; i++)
        {
            os<<"  label = " << tags[i] << ", content = ";
            os << posts[i] << endl;
        }
        os << "trained on " << num_posts << " examples\nvocabulary size = " 
            << uniqwords.size()<< "\n\nclasses:\n";
        for (auto it = uniqtags.begin(); it != uniqtags.end(); it++)
        {
            os << "  " << *it << ", " << num_posts_with_tag[*it]
                << " examples, log-prior = "
                << log(num_posts_with_tag[*it] / static_cast<double>(num_posts))
                << "\n";
        }
        os << "classifier parameters:\n";
        for (auto it = num_post_word_by_label.begin(); it != 
            num_post_word_by_label.end(); it++)
        {
            if (num_post_word_by_label[{it->first.first, it->first.second}]>0)
            os << "  " << it->first.first << ":" << it->first.second << ", count = "
                << num_post_word_by_label[{it->first.first, it->first.second}]
                << ", log-likelihood = " <<
                log(num_post_word_by_label[{it->first.first, it->first.second}] /
                    static_cast<double>(num_posts_with_tag[it->first.first])) << endl;
        }
    }
private:
    void grabwords()
    {
        for (int i = 0; i < num_posts; i++)
        {
            for (auto j = mapost[i].begin(); j != mapost[i].end(); j++) {
                istringstream source(*j);
                string word;
                while (source >> word)
                    uniqwords.insert(word);
            }
        }
    }
    void calculate_count_given()
    {
        for (set<string>::iterator it = uniqwords.begin(); it != uniqwords.end(); it++)
            for (set<string>::iterator ti = uniqtags.begin(); ti != uniqtags.end(); ti++)
            {
                int count = 0;
                for (int i = 0; i < num_posts; i++)
                {
                    if (tags[i] == *ti && mapost[i].find(*it) != mapost[i].end())
                        count++;
                }
                pair<string, string> temp;
                temp.first = *ti;
                temp.second = *it;
                num_post_word_by_label[temp] = count;
            }
    }
    set<string> splitwords(const string& data)
    {
        set<string> thispost;
        istringstream source(data);
        string word;
        while (source >> word)
        {
            thispost.insert(word);
        }
        return thispost;
    }
};
pair<string, double> findPredict(vector<map<string, double>>& prob, const int& i);

void printResult(ostream& os, classifier& train, classifier& test,
    vector<map<string, double>> &probs);

int main(int argc, char* argv[])
{
    cout.precision(3);
    ifstream train, test;
    train.open(argv[1]);
    test.open(argv[2]);
    string debug="";
    if (argv[3])
        debug = argv[3];
 
    if ((argc != 3 && argc != 4) || (debug != "--debug" && debug != "")) {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 1;
    }

    if (!train.is_open()) {
        cout << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    if (!test.is_open()) {
        cout << "Error opening file: " << argv[2] << endl;
        return 1;
    }
    /* do calculations and probability here*/
    csvstream data_in(argv[1]);
    classifier train_data;
    train_data.getData(data_in);
    train_data.calculate_count();
    csvstream test_data(argv[2]);
    classifier test_probs;
    test_probs.getData(test_data);
    vector<map<string, double>> probabilities;
    if (debug == "--debug")
        train_data.debugOption(cout);
    else
        cout << "trained on " << train_data.get_num_posts() << "examples";
    test_probs.getLabelProbs(train_data, probabilities);
    printResult(cout, train_data, test_probs, probabilities);
}


void printResult(ostream& os, classifier& train, classifier& test, 
    vector<map<string, double>> &probs)
{
    os << "\n\ntest data:\n";
    int correct=0;
    for (int i = 0; i < test.get_num_posts(); i++)
    {
        pair<string, double> temp;
        os << "  correct = " << test.getTag(i) << ", predicted = ";
        temp = findPredict(probs, i);
        os << temp.first << ", log-probability score = "
            << temp.second << "\n  content = " << test.getPost(i) <<"\n\n";
        if (test.getTag(i) == temp.first)
            correct++;
    }
    os << "performance: " << correct << " / " << test.get_num_posts()
        << " posts predicted correctly\n";
}

pair<string, double> findPredict(vector<map<string, double>>& prob, const int& i)
{
    pair<string, double> maxE;
    maxE.first = prob[i].begin()->first;
    maxE.second = prob[i].begin()->second;
    for (auto it = prob[i].begin(); it != prob[i].end(); it++)
    {
        if (it->second > maxE.second)
        {
            maxE.first = it->first;
            maxE.second = it->second;
        }
    }
    return maxE;
}