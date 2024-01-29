package mk.finki.ukim.mk.lab.web.controller;

import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.http.HttpSession;
import mk.finki.ukim.mk.lab.model.Author;
import mk.finki.ukim.mk.lab.model.Book;
import mk.finki.ukim.mk.lab.service.AuthorService;
import mk.finki.ukim.mk.lab.service.BookService;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.thymeleaf.context.WebContext;
import org.thymeleaf.web.IWebExchange;
import org.thymeleaf.web.servlet.JakartaServletWebApplication;

import java.io.IOException;
import java.time.LocalDate;
import java.util.List;
import java.util.Objects;

@Controller
@RequestMapping("/author")
public class AuthorController {

    private final BookService bookService;
    private final AuthorService authorService;

    public AuthorController(BookService bookService, AuthorService authorService) {
        this.bookService = bookService;
        this.authorService = authorService;
    }



@GetMapping
public String listAuthors(HttpServletRequest req, Model model)
{
    model.addAttribute("authors",authorService.listAuthors());
    String isbn= (String) req.getSession().getAttribute("isbn");
    model.addAttribute("isbn",isbn);
    return "authorList";

}
    @PostMapping
    public String AddAuthorToBook(HttpServletRequest request,@RequestParam String authorId, Model model)
    {
        Long id=Long.valueOf((String)authorId);
        model.addAttribute("id",id);
        String isbn=(String)request.getSession().getAttribute("isbn");
        bookService.addAuthorToBook(id,isbn);
        return "redirect:/bookdetails";

    }

    @GetMapping("/edit-author-form/{id}")
    public String EditAuthorPage(@PathVariable Long id, Model model)
    {
        List<Author> authors=this.authorService.listAuthors();
        model.addAttribute("authors",authors);
        if(this.authorService.findById(id).isPresent())
        {
            Author author=this.authorService.findById(id).get();
            model.addAttribute("author",author);
            return "add-author";
        }
        return "redirect:/author?error=NotFoundException";
    }
    @PostMapping("/delete-author/{id}")
    public String deleteAuthor(@PathVariable Long id)
    {
        this.authorService.DeleteById(id);
        return "redirect:/author";
    }
    @GetMapping("/add-author-form")
    public String AddAuthorForm(Model model)
    {
        List<Author>authors=this.authorService.listAuthors();
        model.addAttribute("authors",authors);
        return "add-author";
    }
    @PostMapping("/add-author")
    public String SaveAuthor(@RequestParam Long Id, @RequestParam String name, @RequestParam String surname, @RequestParam String biography,@RequestParam LocalDate time)
    {
        this.authorService.Save(Id,name,surname,biography,time);
        return "redirect:/author";
    }

}
