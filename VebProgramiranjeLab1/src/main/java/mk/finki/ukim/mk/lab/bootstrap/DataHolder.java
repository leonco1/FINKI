package mk.finki.ukim.mk.lab.bootstrap;

import jakarta.annotation.PostConstruct;
import mk.finki.ukim.mk.lab.model.Author;
import mk.finki.ukim.mk.lab.model.Book;
import mk.finki.ukim.mk.lab.model.BookSales;
import mk.finki.ukim.mk.lab.model.BookStore;

import mk.finki.ukim.mk.lab.repository.jpa.AuthorRepository;
import mk.finki.ukim.mk.lab.repository.jpa.BookRepository;
import mk.finki.ukim.mk.lab.repository.jpa.BookSalesRepository;
import mk.finki.ukim.mk.lab.repository.jpa.BookStoreRepository;
import org.springframework.stereotype.Component;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

@Component
public class DataHolder {

    private final BookRepository bookRepository;
    private final AuthorRepository authorRepository;
    private final BookStoreRepository bookStoreRepository;
    private final BookSalesRepository bookSalesRepository;

    public DataHolder(BookRepository bookRepository, AuthorRepository authorRepository, BookStoreRepository bookStoreRepository, BookSalesRepository bookSalesRepository) {
        this.bookRepository = bookRepository;
        this.authorRepository = authorRepository;
        this.bookStoreRepository = bookStoreRepository;
        this.bookSalesRepository = bookSalesRepository;
    }

    @PostConstruct
    public void init(){
        List<Author> authors = new ArrayList<>();
        List<Book> books = new ArrayList<>();
        List<BookStore> bookStores = new ArrayList<>();
        List<BookSales> bookSales=new ArrayList<>();
        if (authorRepository.count() == 0){
            authors.add(new Author(
                    "William",
                    "Shakespeare",
                    "William Shakespeare is one of the most celebrated playwrights and poets in English literature. He was born in Stratford-upon-Avon, England. His works, including plays like Hamlet,Romeo and Juliet,\" and \"Macbeth,\" have had a profound impact on the world of literature and drama"
            ));
            authors.add(new Author(
                    "George R.R.",
                    "Martin",
                    "George R.R. Martin, an American author, is widely known for his epic fantasy series \"A Song of Ice and Fire,\" which inspired the television series Game of Thrones. Born in Bayonne, New Jersey, Martin is celebrated for his intricate plots and complex characters in the fantasy genre."
            ));

            authors.add(new Author(
                    "J.R.R.",
                    "Tolkien",
                    "J.R.R. Tolkien, an English writer, philologist, and professor, is considered the father of modern fantasy literature. Born in Bloemfontein, South Africa, his iconic works, including \"The Hobbit\" and \"The Lord of the Rings,\" have had a profound and enduring impact on the fantasy genre and literature as a whole."
            ));
            authors.add(new Author(
                    "Mark",
                    "Twain",
                    "Mark Twain, born Samuel Clemens in Florida, Missouri, was an American author and humorist. His classic works, including The Adventures of Tom Sawyer and Adventures of Huckleberry Finn,\" reflect his keen observations of American society and human nature."
            ));

            authors.add(new Author(
                    "J.K.",
                    "Rowling",
                    "J.K. Rowling, a British author, gained worldwide fame for her Harry Potter series. Born in Yate, Gloucestershire, her magical world of wizards and muggles has captivated readers of all ages, making her one of the best-selling authors in history."
            ));

            authorRepository.saveAll(authors);
        }
        if(bookSalesRepository.count()==0)
        {
            bookSales.add(new BookSales(1));
            bookSales.add(new BookSales(2));
            bookSales.add(new BookSales(3));
            bookSales.add(new BookSales(4));
            bookSalesRepository.saveAll(bookSales);
        }
        if (bookStoreRepository.count() == 0){
            bookStores.add(new BookStore(
                    "Prosvetno Delo",
                    "Prilep",
                    "Address 1"
            ));
            bookStores.add(new BookStore(
                    "Book Haven",
                    "New York City",
                    "123 Main Street"
            ));

            bookStores.add(new BookStore(
                    "Paper Trails",
                    "Los Angeles",
                    "456 Oak Avenue"
            ));

            bookStores.add(new BookStore(
                    "Literatura",
                    "Veles",
                    "Address 4"
            ));
            bookStores.add(new BookStore(
                    "Akademska Kniga",
                    "Skopje",
                    "Address 5"
            ));
            bookStoreRepository.saveAll(bookStores);
        }

        if (bookRepository.count() == 0){
            authors = authorRepository.findAll();
            bookStores=bookStoreRepository.findAll();
            bookSales=bookSalesRepository.findAll();
            books.add(new Book(
                    "978-0-316-03859-9",
                    "Hamlet",
                    "Tragedy",
                    1600,
                    new ArrayList<Author>(Arrays.asList(authors.get(0),authors.get(1))),
                    bookStores.get(0),bookSales.get(1)
            ));
            books.add(new Book(
                    "978-1-250-04657-8",
                    "Pride and Prejudice",
                    "Romance",
                    1816,
                    new ArrayList<Author>(Arrays.asList(authors.get(1),authors.get(2))),
                    bookStores.get(1),bookSales.get(2)
            ));
            books.add(new Book(
                    "978-0-553-21361-4",
                    "Great Expectations",
                    "Bildungsroman",
                    1861,
                    new ArrayList<Author>(Arrays.asList(authors.get(2),authors.get(3))),
                    bookStores.get(2),bookSales.get(3)
            ));
            books.add(new Book(
                    "978-0-06-112008-4",
                    "Murder on the Orient Express",
                    "Detective Fiction",
                    1934,
                    new ArrayList<Author>(Arrays.asList(authors.get(3),authors.get(4))),
                    bookStores.get(3),bookSales.get(1)
            ));
            books.add(new Book(
                    "978-0-451-52478-1",
                    "One Hundred Years of Solitude",
                    "Magical Realism",
                    1967,
                    new ArrayList<Author>(Collections.singletonList(authors.get(4))),
                    bookStores.get(4),bookSales.get(2)
            ));
            books.add(new Book(
                    "978-0-451-52478-2",
                    "One Hundred Years of Solitude2",
                    "Magical Realism",
                    1967,
                    new ArrayList<Author>(Collections.singletonList(authors.get(1))),
                    bookStores.get(0),bookSales.get(0)
            ));
            books.add(new Book(
                    "978-0-451-52478-3",
                    "One Hundred Years of Solitude3",
                    "Magical Realism",
                    1600,
                    new ArrayList<Author>(Collections.singletonList(authors.get(2))),
                    bookStores.get(3),bookSales.get(0)
            ));
            bookRepository.saveAll(books);
        }
    }
}
