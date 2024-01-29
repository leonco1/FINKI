//package mk.finki.ukim.mk.lab.repository.inmemory;
//
//import mk.finki.ukim.mk.lab.bootstrap.DataHolder;
//import mk.finki.ukim.mk.lab.model.Author;
//import org.springframework.stereotype.Repository;
//
//import java.time.LocalDate;
//import java.util.List;
//import java.util.Optional;
//@Repository
//public class InMemoryAuthorRepository {
//
//    public List<Author> findAll()
//    {
//        return DataHolder.a;
//    }
//    public Optional<Author> findById(Long id)
//    {
//        return DataHolder.authors.stream().filter(i->i.getId().equals(id)).findFirst();
//    }
//
//    public Optional<Author>Save(Long id, String name, String surname, String biography, LocalDate localDate)
//    {
//
//        Author author=new Author(id,name,surname,localDate);
//        DataHolder.authors.removeIf(i->i.getId().equals(author.getId()));
//        DataHolder.authors.add(author);
//        return Optional.of(author);
//    }
//    public void DeleteById(Long Id)
//    {
//        DataHolder.authors.removeIf(i->i.getId().equals(Id));
//    }
//}
