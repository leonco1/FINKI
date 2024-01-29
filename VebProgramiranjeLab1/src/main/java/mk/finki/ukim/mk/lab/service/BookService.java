package mk.finki.ukim.mk.lab.service;

import mk.finki.ukim.mk.lab.model.Author;
import mk.finki.ukim.mk.lab.model.Book;

import java.util.List;
import java.util.Optional;

public interface BookService {
    List<Book> listBooks();
    Author addAuthorToBook(Long authorId, String isbn);
    Book findBookByIsbn(String isbn);
  //  Map<String,List<String>>listGenre(List<Book>list);
    List<Book>getYears(Integer year);
    public Optional<Book> Save(String title, String isbn, String genre, Integer year, Long Id);
    Optional<Book> addBook(String title, String isbn, String genre, int year, long bookStoreId);
    Optional<Book> editBook(Long bookId,String title, String isbn, String genre, int year, long bookStoreId,long bookSalesId);
    public Optional<Book> findById(Long id);
    public void DeleteById(Long id);

}
