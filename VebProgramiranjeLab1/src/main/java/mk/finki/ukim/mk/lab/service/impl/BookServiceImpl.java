package mk.finki.ukim.mk.lab.service.impl;

import mk.finki.ukim.mk.lab.model.Author;
import mk.finki.ukim.mk.lab.model.Book;
import mk.finki.ukim.mk.lab.model.BookSales;
import mk.finki.ukim.mk.lab.model.BookStore;
import mk.finki.ukim.mk.lab.repository.jpa.AuthorRepository;
import mk.finki.ukim.mk.lab.repository.jpa.BookRepository;
import mk.finki.ukim.mk.lab.repository.jpa.BookSalesRepository;
import mk.finki.ukim.mk.lab.repository.jpa.BookStoreRepository;
import mk.finki.ukim.mk.lab.service.BookService;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@Service
public class BookServiceImpl implements BookService {
    private final AuthorRepository authorRepository;
    private final BookRepository bookRepository;
    private final BookStoreRepository bookStoreRepository;
    private final BookSalesRepository bookSalesRepository;

    public BookServiceImpl(AuthorRepository authorRepository, BookRepository bookRepository, BookStoreRepository bookStoreRepository, BookSalesRepository bookSalesRepository) {
        this.authorRepository = authorRepository;
        this.bookRepository = bookRepository;
        this.bookStoreRepository=bookStoreRepository;
        this.bookSalesRepository = bookSalesRepository;
    }

    @Override
    public List<Book> listBooks() {
        return bookRepository.findAll();
    }

    @Override
    public Author addAuthorToBook(Long authorId, String isbn) {
        Author author= authorRepository.findById(authorId).orElse(null);
        Book book=bookRepository.findByIsbn(isbn);
        List<Book>bookList=bookRepository.findAll();
        if (author != null)
        {
            book.getAuthors().remove(author);
            book.getAuthors().add(author);
        }
        bookList.removeIf(i-> i.getIsbn().equals(book.getIsbn()));
        bookList.add(book);
       return this.authorRepository.save(author);

    }

    @Override
    public Book findBookByIsbn(String isbn) {
        return bookRepository.findByIsbn(isbn);
    }

    @Override
    public Optional<Book> addBook(String title, String isbn, String genre, int year, long bookStoreId) {
        Optional<BookStore> foundBookstore = bookStoreRepository.findAll().stream().filter(x -> x.getId().equals(bookStoreId)).findFirst();
        if (title.isEmpty() || isbn.isEmpty() || genre.isEmpty() || foundBookstore.isEmpty()){
            throw new IllegalArgumentException();
        }
        Book newBook = new Book(String.valueOf((long) (Math.random()*1000)),title,genre,year,new ArrayList<>(),foundBookstore.get());
        bookRepository.save(newBook);
        return Optional.of(newBook);
    }

    @Override
    public Optional<Book> editBook(Long bookId, String title, String isbn, String genre, int year, long bookStoreId,long bookSalesId) {
        Optional<BookStore> foundBookstore = bookStoreRepository.findAll().stream().filter(x -> x.getId().equals(bookStoreId)).findFirst();
        Optional<Book> foundBook = bookRepository.findById((long) bookId);
        //Optional<BookSales>bookSales=bookSalesRepository.findAll().stream().filter(i->i.get)
        if (foundBook.isEmpty() || foundBookstore.isEmpty() || title.isEmpty() || isbn.isEmpty() || genre.isEmpty()){
            throw new IllegalArgumentException();
        }
        Optional<BookSales> foundSales = bookSalesRepository.findAll().stream().filter(x -> x.getId().equals(bookSalesId)).findFirst();

        foundBook.get().setTitle(title);
        foundBook.get().setIsbn(isbn);
        foundBook.get().setGenre(genre);
        foundBook.get().setYear(year);
        foundBook.get().setBookStore(foundBookstore.get());
        foundBook.get().setBookSales(foundSales.get());

        bookRepository.save(foundBook.get());
        return foundBook;
    }

    //    @Override
//    public Map<String, List<String>> listGenre(List<Book>list) {
//       return bookRepository.listGenres();
//
//    }
    @Override
    public void DeleteById(Long bookId)
    {
        Optional<Book> deleteBook = bookRepository.findById((long)bookId);
        if (deleteBook.isEmpty()){
            throw new IllegalArgumentException();
        }

        bookRepository.delete(deleteBook.get());
    }

    @Override
    public List<Book> getYears(Integer year) {
       return listBooks().stream().filter(book -> {
            Integer yearr=book.getYear();
            return yearr.equals(year);
        }).collect(Collectors.toList());

    }

    @Override
    public Optional<Book> Save(String title, String isbn, String genre, Integer year, Long Id) {
        BookStore bookStore=bookStoreRepository.findById(Id).get();
        return Optional.of(this.bookRepository.save(new Book(isbn,title,genre,year,bookStore)));
    }

    @Override
    public Optional<Book> findById(Long id) {
        return this.bookRepository.findById(id);
    }



}
