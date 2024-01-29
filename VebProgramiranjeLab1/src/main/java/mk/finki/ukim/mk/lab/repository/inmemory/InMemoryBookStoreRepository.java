//package mk.finki.ukim.mk.lab.repository.inmemory;
//
//import mk.finki.ukim.mk.lab.bootstrap.DataHolder;
//import mk.finki.ukim.mk.lab.model.BookStore;
//import org.springframework.stereotype.Repository;
//
//import java.util.List;
//import java.util.Optional;
//
//@Repository
//public class InMemoryBookStoreRepository {
//
//    public List<BookStore> findAll()
//    {
//        return DataHolder.bookStores;
//    }
//    public Optional<BookStore>findByID(Long id)
//    {
//        return DataHolder.bookStores.stream().filter(i->i.getId().equals(id)).findFirst();
//    }
//}
