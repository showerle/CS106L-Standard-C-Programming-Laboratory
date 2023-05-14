#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <stdexcept>
#include <unordered_map>
#include "wikiscraper.h"
#include "error.h"

using std::cout;            using std::endl;
using std::cerr;            using std::string;
using std::unordered_map;   using std::unordered_set;

/*
 * You should delete the code in this function and
 * fill it in with your code from part A of the assignment.
 *
 * If you used any helper functions, just put them above this function.
 */


bool valid_wikilink(const string& link) {
    // replace these lines!
    if (link.find(":") == string::npos && link.find("#") == string::npos){
        return true;
    }else{
        return false;
    }
}

unordered_set<string> findWikiLinks(const string& inp) {
    /* Delimiter for start of a link  */
    static const string delim = "href=\"/wiki/";

    unordered_set<string> ret;

    auto url_start = inp.begin();
    auto end = inp.end();

    while(true) {


        auto link_start = std::search(url_start, end, delim.begin(), delim.end());
        if (link_start == end ) break;

        char element = '\"';
        auto url_end = std::find(link_start + delim.length(), end, element);

        string link(link_start + delim.length() , url_end);        

        if(valid_wikilink(link)){
            ret.insert(link);
        }

        url_start = url_end;

    }
    return ret;

}


/*
 * ==================================================================================
 * |                Don't edit anything below here, but take a peek!                |
 * ==================================================================================
 */
unordered_set<string> WikiScraper::getLinkSet(const string& page_name) {
    if(linkset_cache.find(page_name) == linkset_cache.end()) {
        auto links = findWikiLinks(getPageSource(page_name));
        linkset_cache[page_name] = links;
    }
    return linkset_cache[page_name];
}


WikiScraper::WikiScraper() {
    (void)getPageSource("Main_Page");
}


string createPageUrl(const string& page_name) {
    return "https://en.wikipedia.org/wiki/" + page_name;
}

void notFoundError(const string& msg, const string& page_name, const string& url) {
    const string title = "    AN ERROR OCCURED DURING EXECUTION.    ";
    const string border(title.size() + 4, '*');
    cerr << endl;
    errorPrint(border);
    errorPrint("* " + title + " *");
    errorPrint(border);
    errorPrint();
    errorPrint("Reason: " + msg);
    errorPrint();
    errorPrint("Debug Information:");
    errorPrint();
    errorPrint("\t- Input parameter: " + page_name);
    errorPrint("\t- Attempted url: " + url);
    errorPrint();
}

string WikiScraper::getPageSource(const string &page_name) {
    const static string not_found = "Wikipedia does not have an article with this exact name.";
    if(page_cache.find(page_name) == page_cache.end()) {
        string url = createPageUrl(page_name);
        // using the cpr library to get the HTML content of a webpage!
        // we do so by aking a GET REST request to a wikipedia webpage, which
        // returns the content of the webpage. when this assignment was on QtCreator,
        // we had a whole separate assignment for making sure an alternate Internet Library
        // (not cpr) was working on your personal pc. look how simple it is now!
        cpr::Response r = cpr::Get(cpr::Url{url});

        string ret = r.text;
        if (r.status_code != 200) {
            // cout << "Couldn't get page source. Have you entered a valid link?" << endl;
            notFoundError("Couldn't get page source. Have you entered a valid link?", page_name, url);
            return "";
        }
        if(std::search(ret.begin(), ret.end(), not_found.begin(), not_found.end()) != ret.end()){
            // cout << "Page does not exist!" << endl;
            notFoundError("Page does not exist!", page_name, url);
            return "";
        }
        size_t indx = ret.find("plainlinks hlist navbar mini");
        if(indx != string::npos) {
            return ret.substr(0, indx);
        }
        page_cache[page_name] = ret;
    }
    return page_cache[page_name];
}





