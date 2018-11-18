
//  Massage.h
//  邮件管理系统
//
//  Created by 王舒啸 on 2018/10/13.
//  Copyright © 2018 王舒啸. All rights reserved.
//

#ifndef Massage_h
#define Massage_h

#include<string>
#include<set>

using std::string;
using std::set;

class Folder;
class Massage{
    friend class Folder;
private:
    string passage;
    set<Folder*> folders;
    void add_to_folder( Massage &);
    void delete_from_folder();
    void move_to_folder( Massage &);
    void clear();
public:
    explicit Massage (const string &s=string()):passage(s){};
    Massage (Massage& m);
    Massage (Massage &&m) noexcept;
    Massage& operator=( Massage& m);
    Massage& operator=(Massage &&m) noexcept;
    ~Massage(){clear();};
    void save ( Folder& f);
    void remove ( Folder& f);
};

class Folder{
private:
    set<Massage*>mass_fold;
    void add_massage(Folder &);
    void remove_massage();
public:
    explicit Folder(set<Massage*>s):mass_fold(s){};
    explicit Folder(std::initializer_list <Massage*> il);
    Folder(Folder &f);
    Folder& operator = ( Folder &f);
    ~Folder ();
    void add( Massage *m);
    void remove (Massage *m);
};

#endif /* Massage_h */
