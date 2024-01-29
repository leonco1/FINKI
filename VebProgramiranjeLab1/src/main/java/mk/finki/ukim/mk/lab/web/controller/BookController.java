package mk.finki.ukim.mk.lab.web.controller;

import jakarta.servlet.http.HttpServletRequest;
import mk.finki.ukim.mk.lab.model.Author;
import mk.finki.ukim.mk.lab.model.Book;
import mk.finki.ukim.mk.lab.service.BookService;
import mk.finki.ukim.mk.lab.service.BookStoreService;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@Controller
@RequestMapping("/books")
public class BookController {
    private final BookService bookService;
    private final BookStoreService bookStoreService;


    public BookController(BookService bookService, BookStoreService bookStoreService) {
        this.bookService = bookService;
        this.bookStoreService = bookStoreService;
    }

    @GetMapping
    public String getBooksPage(@RequestParam(required = false) String error, HttpServletRequest req,Model model)
    {

        String year = (req.getParameter("searchTerm"));
        if (year == "" || year == null) {
            model.addAttribute("books", bookService.listBooks());
            //model.addAttribute("genres", bookService.listGenre(bookService.listBooks()));
        } else {
            Integer yearr = Integer.valueOf(year);
            List<Book> bookList = bookService.getYears(yearr);
            model.addAttribute("books", bookList);

        }
        if(error!=null&&!error.isEmpty())
        {
            model.addAttribute("hasError", true);
            model.addAttribute("error", error);
        }

        return "listbooks";
    }
    @PostMapping
    public String submit(HttpServletRequest request, Model model) {
        String isbn = (String) request.getParameter("bookIsbn");
        String year = request.getParameter("searchTerm");
        model.addAttribute("books", isbn);
        request.getSession().setAttribute("isbn",isbn);
        return "redirect:/author";
    }
    @GetMapping("/edit-form/{id}")
            public String EditProductPage(@PathVariable Long id,Model model)
    {
        List<Book>books=this.bookService.listBooks();
        model.addAttribute("books",books);
        model.addAttribute("BookStores",this.bookStoreService.findAll());
        Book book=this.bookService.findById(id).get();
        if(this.bookService.editBook(book.getId(),book.getTitle(),book.getIsbn(),book.getGenre(),book.getYear(),
                book.getBookStore().getId(),book.getBookSales().getId()).isPresent())        {
            model.addAttribute("book",book);
            return "add";
        }
        return "redirect:/books?error=NotFoundException";
    }
    @PostMapping("/delete/{id}")
    public String deleteProduct(@PathVariable Long id)
    {this.bookService.DeleteById(id);
    return "redirect:/books";
    }
  @GetMapping("/add-form")
    public String addBookPage(Model model)
  {
      List<Book>books=this.bookService.listBooks();
        model.addAttribute("books",books);
        model.addAttribute("BookStores",this.bookStoreService.findAll());
        return "add";
  }
  @PostMapping("/add")
    public String SaveBook(@RequestParam String title, @RequestParam String isbn, @RequestParam String genre, @RequestParam Integer year,@RequestParam Long ID )
  {
    this.bookService.addBook(title,isbn,genre,year,ID);
      return "redirect:/books";
  }

}
