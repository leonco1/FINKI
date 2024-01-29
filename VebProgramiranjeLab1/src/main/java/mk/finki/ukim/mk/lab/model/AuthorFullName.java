package mk.finki.ukim.mk.lab.model;

import lombok.AllArgsConstructor;

import java.io.Serializable;

@AllArgsConstructor
public class AuthorFullName implements Serializable {
String name;
String surname;

    public String getName() {
        return name;
    }

    public AuthorFullName() {
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSurname() {
        return surname;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }
}
