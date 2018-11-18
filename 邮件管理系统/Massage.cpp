//
//  Massage.cpp
//  邮件管理系统
//
//  Created by 王舒啸 on 2018/10/13.
//  Copyright © 2018 王舒啸. All rights reserved.
//

#include"Massage.h"

void Massage::add_to_folder( Massage &m){
    for (auto f:m.folders){
        f->add(&m);
    }
}

void Massage::delete_from_folder(){
    for (auto f:folders)
        f->remove(this);
}

void Massage::move_to_folder(Massage &m){
    passage = std::move(m.passage);
    folders = std::move(m.folders);
    for (auto f:folders){
        f->remove(&m);
        f->add(this);
    }
    m.folders.clear();
}

Massage::Massage ( Massage& m){
    passage = m.passage;
    folders = m.folders;
    add_to_folder(m);
}

Massage& Massage::operator=( Massage & m){
    clear();
    passage = m.passage;
    folders = m.folders;
    add_to_folder(m);
    return *this;
}

Massage::Massage (Massage && m) noexcept{
    move_to_folder(m);
}

Massage& Massage::operator=(Massage &&m) noexcept{
    if (this != &m){
        delete_from_folder();
        move_to_folder(m);
    }
    return *this;
}

void Massage::save( Folder &f){
    folders.insert(&f);
    f.add(this);
}

void Massage::remove(Folder &f){
    folders.erase(&f);
    f.remove(this);
}

void Massage::clear(){
    if (!folders.empty()){
        delete_from_folder();
        folders.clear();
    }
}

void Folder:: add_massage( Folder& f){
    for (auto &i:f.mass_fold){
        i->save(f);
    }
}
void Folder::remove_massage(){
    for (auto &i :mass_fold){
        i->remove(*this);
    }
}

Folder::Folder (std::initializer_list <Massage*> il){
    for (auto &i:il)
        mass_fold.insert(i);
}

Folder::Folder (Folder &f){
    mass_fold = f.mass_fold;
    add_massage(f);
}

Folder& Folder:: operator=(Folder &f){
    remove_massage();
    mass_fold = f.mass_fold;
    add_massage(f);
    return *this;
}

Folder::~Folder(){
    if (!mass_fold.empty()){
        remove_massage();
    }
}

void Folder:: add( Massage *m){
    mass_fold.insert(m);
}

void Folder::remove(Massage *m){
    mass_fold.erase(m);
}
