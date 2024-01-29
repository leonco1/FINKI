package mk.finki.ukim.mk.lab.service.impl;

import mk.finki.ukim.mk.lab.model.BookStore;
import mk.finki.ukim.mk.lab.repository.jpa.BookRepository;
import mk.finki.ukim.mk.lab.repository.jpa.BookStoreRepository;
import mk.finki.ukim.mk.lab.service.BookStoreService;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class BookStoreServiceImpl implements BookStoreService {
    private final BookStoreRepository bookStoreRepository;
    private final BookRepository bookRepository;

    public BookStoreServiceImpl(BookStoreRepository bookStoreRepository, BookRepository bookRepository) {
        this.bookStoreRepository = bookStoreRepository;
        this.bookRepository = bookRepository;
    }


    @Override
    public List<BookStore> findAll() {
        return bookStoreRepository.findAll();
    }


}
