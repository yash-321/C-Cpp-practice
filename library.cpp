/* complete this file */

#include "library.h"
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>  // needed for open
#include <sys/stat.h>   // needed for open
#include <fcntl.h>      // needed for open
#include <unistd.h>     // needed for read and write
#include <string.h>
#include <string>

/* Document methods */

void Document::updateTitle(const char *newTitle) {
	free(_title);
	_title = (char*) malloc((strlen(newTitle) + 1) * sizeof(char));
	strcpy(_title, newTitle);
}
void Document::updateYear(int newYear) {
	_year = newYear;
}
void Document::updateQuantity(int newQuantity) {
	_quantity = newQuantity;
}
char* Document::getTitle() {
	return _title;
}
int Document::getYear() {
	return _year;
}
int Document::getQuantity() {
	return _quantity;
}

int Document::borrowDoc() {
	if (_quantity > 0) {
		_quantity--;
		return 0;
	}
	return -1;
}

void Document::returnDoc() {
	_quantity++;
}


/* Novel methods */

Novel::Novel(const char *title, const char *author, int year, int quantity) {
	_year = year;
	_quantity = quantity;
	_title = (char*) malloc((strlen(title) + 1) * sizeof(char));
	strcpy(_title, title);
	_author = (char*) malloc((strlen(author) + 1) * sizeof(char));
	strcpy(_author, author);
}

Novel::~Novel() {
	free(_title);
	free(_author);
}

document_type Novel::getDocType() {
	return DOC_NOVEL;
}

void Novel::print() {
	printf("Novel, title: %s, author: %s, year: %d, quantity: %d\n", _title, _author, _year, _quantity);
}

void Novel::updateAuthor(const char *newAuthor) {
	free(_author);
	_author = (char*) malloc((strlen(newAuthor) + 1) * sizeof(char));
	strcpy(_author, newAuthor);
}

char* Novel::getAuthor() {
	return _author;
}


/* Comic methods */

Comic::Comic(const char *title, const char *author, int issue, int year, int quantity) {
	_issue = issue;
	_year = year;
	_quantity = quantity;
	_title = (char*) malloc((strlen(title) + 1) * sizeof(char));
	strcpy(_title, title);
	_author = (char*) malloc((strlen(author) + 1) * sizeof(char));
	strcpy(_author, author);
}

Comic::~Comic() {
	free(_title);
	free(_author);
}

document_type Comic::getDocType() {
	return DOC_COMIC;
}

void Comic::print() {
	printf("Comic, title: %s, author: %s, issue: %d, year: %d, quantity: %d\n", _title, _author, _issue, _year, _quantity);
}

void Comic::updateAuthor(const char *newAuthor) {
	free(_author);
	_author = (char*) malloc((strlen(newAuthor) + 1) * sizeof(char));
	strcpy(_author, newAuthor);
}

void Comic::updateIssue(int newIssue) {
	_issue = newIssue;
}

char* Comic::getAuthor() {
	return _author;
}

int Comic::getIssue() {
	return _issue;
}



/* Magazine methods */

Magazine::Magazine(const char *title, int issue, int year, int quantity) {
	_issue = issue;
	_year = year;
	_quantity = quantity;
	_title = (char*) malloc((strlen(title) + 1) * sizeof(char));
	strcpy(_title, title);
}

Magazine::~Magazine() {
	free(_title);
}

document_type Magazine::getDocType() {
	return DOC_MAGAZINE;
}

void Magazine::print() {
	printf("Magazine, title: %s, issue: %d, year: %d, quantity: %d\n", _title, _issue, _year, _quantity);
}

void Magazine::updateIssue(int newIssue) {
	_issue = newIssue;
}

int Magazine::getIssue() {
	return _issue;
}


/* Library methods */

Library::Library(){

}

void Library::print() {
	for(int i=0; i<_docs.size(); i++) {
		_docs[i]->print();
	}
}

int Library::dumpCSV(const char *filename) {
	int myfile = open(("./%s", filename), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if(myfile == -1) {
		printf("error with open\n");
        return -1;
    }
	for(int i=0; i<_docs.size(); i++) {
		if (_docs[i]->getDocType() == DOC_NOVEL){
			Novel *n = static_cast<Novel*>(_docs[i]);
			char *buffer = (char*) malloc(100 * sizeof(char));
			sprintf(buffer,"novel,%s,%s,,%d,%d\n", n->getTitle(), n->getAuthor(), n->getYear(), n->getQuantity());
			if(write(myfile, buffer, strlen(buffer)) != strlen(buffer)) {
		        free(buffer);
		        printf("issue writing\n");
		        close(myfile);
		        return -1;
		    }
		    free(buffer);
		}
		if (_docs[i]->getDocType() == DOC_COMIC){
			Comic *c = static_cast<Comic*>(_docs[i]);
			char *buffer = (char*) malloc(100 * sizeof(char));
			sprintf(buffer, "comic,%s,%s,%d,%d,%d\n", _docs[i]->getTitle(), c->getAuthor(), c->getIssue(), _docs[i]->getYear(), _docs[i]->getQuantity());
			if(write(myfile, buffer, strlen(buffer)) != strlen(buffer)) {
		        free(buffer);
		        printf("issue writing\n");
		        close(myfile);
		        return -1;
		    }
		    free(buffer);
		}
		if (_docs[i]->getDocType() == DOC_MAGAZINE){
			Magazine *m = static_cast<Magazine*>(_docs[i]);
			char *buffer = (char*) malloc(100 * sizeof(char));
			sprintf(buffer, "magazine,%s,,%d,%d,%d\n", _docs[i]->getTitle(), m->getIssue(), _docs[i]->getYear(), _docs[i]->getQuantity());
			if(write(myfile, buffer, strlen(buffer)) != strlen(buffer)) {
		        free(buffer);
		        printf("issue writing\n");
		        close(myfile);
		        return -1;
		    }
		    free(buffer);
		}
	}
	close(myfile);
	return 0;
}

Document* Library::searchDocument(const char *title) {
	for(int i=0; i<_docs.size(); i++) {
		if (strcmp(_docs[i]->getTitle(), title) == 0){
			return _docs[i];
		}
	}
	return NULL;
}

int Library::addDocument(Document *d) {
	if (!this->searchDocument(d->getTitle())){
		_docs.push_back(d);
		return 0;
	}
	return -1;
}

int Library::delDocument(const char *title) {
	for(int i=0; i<_docs.size(); i++) {
		if (strcmp(_docs[i]->getTitle(), title) == 0){
			_docs.erase(_docs.begin() + i);
			return 0;
		}
	}
	return -1;
}

int Library::countDocumentOfType(document_type t) {
	int count = 0;
	for(int i=0; i<_docs.size(); i++) {
		if (_docs[i]->getDocType() == t){
			count++;
		}
	}
	return count;
}

int Library::borrowDoc(const char *title) {
	for(int i=0; i<_docs.size(); i++) {
		if (strcmp(_docs[i]->getTitle(), title) == 0){
			if(_docs[i]->getQuantity() > 0){
				_docs[i]->borrowDoc();
				return 0;
			}
			return -1;
		}
	}
	return -1;
}

int Library::returnDoc(const char *title) {
	for(int i=0; i<_docs.size(); i++) {
		if (strcmp(_docs[i]->getTitle(), title) == 0){
			_docs[i]->returnDoc();
			return 0;
		}
	}
	return -1;
}
