package mk.finki.ukim.mk.lab.repository.jpa;

import mk.finki.ukim.mk.lab.bootstrap.DataHolder;
import mk.finki.ukim.mk.lab.model.Author;
import mk.finki.ukim.mk.lab.model.Book;
import mk.finki.ukim.mk.lab.model.BookStore;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Map;
import java.util.Optional;
@Repository
public interface BookRepository extends JpaRepository<Book,String> {
    public List<Book> findAll();
    public Book findByIsbn(String isbn);
    public Optional<Book> findById(Long id);
    public void deleteById(Long Id);
}
