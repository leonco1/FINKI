package mk.finki.ukim.mk.lab.model;

import jakarta.persistence.AttributeConverter;
import jakarta.persistence.Converter;

@Converter
public class AuthorFullNameConverter implements AttributeConverter<AuthorFullName,String> {
    private static final String SEPARATOR = ", ";
    private boolean check(String name)
    {
        return name!=null&&!name.isEmpty();
    }
    @Override
    public String convertToDatabaseColumn(AuthorFullName authorFullname) {
        if(authorFullname==null)
            return null;
        StringBuilder stringBuilder=new StringBuilder();
        if(check(authorFullname.getName()))
        {
        stringBuilder.append(authorFullname.getName());
        stringBuilder.append(SEPARATOR);
        }
        if(check(authorFullname.getSurname()))
        {
            stringBuilder.append(authorFullname.getSurname());
        }
        return stringBuilder.toString();
    }

    @Override
    public AuthorFullName convertToEntityAttribute(String s) {
        if(!check(s))
            return null;
        String[] pieces = s.split(SEPARATOR);
        if(pieces==null||pieces.length==0)
            return null;
        AuthorFullName authorFullName=new AuthorFullName();
        String name=!pieces[0].isEmpty()?pieces[0]:null;
        if(s.contains(SEPARATOR))
        {
            authorFullName.setName(name);
            if(pieces.length>=2&&check(pieces[1]))
            {
                authorFullName.setSurname(pieces[1]);
            }
            else {
                authorFullName.setSurname(name);
            }
        }
        return authorFullName;
    }
}
