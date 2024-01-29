package mk.finki.ukim.mk.lab.service;

import mk.finki.ukim.mk.lab.model.Author;
import mk.finki.ukim.mk.lab.model.exceptions.NotFoundException;

import java.time.LocalDate;
import java.util.List;
import java.util.Optional;

public interface AuthorService {
    List<Author> listAuthors();
    Optional<Author> findById(Long id);
    void Add(Long id);
    Optional<Author>Save(Long id, String name, String surname, String biography, LocalDate localDate);
    void DeleteById(Long Id);
}

