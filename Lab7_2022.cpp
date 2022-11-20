#include <iostream>
using namespace std;
const int days_for_simulation = 30;
const int books_q = 100;
const int visitors_q = 30;
const int max_reader_scores = 100;
const int max_readed_books = 100;
const string genre_list[4] = { "Detective", "Love story", "Fantasy\t", "Sci-fi\t"};
const string size_preferences[3] = { "Big", "Mid", "Small" };
const string authors_list[10] = { "John Tolkien", "Jane Austen", "Philip Pullman", "Douglas Adams", "Joanne Rowling",
"Harper Lee", "Alan Milne", "George Orwell", "Clive Lewis", "Charlotte Bront" };
const string book_names[10] = { "To Kill a Mockingbird", "1984\t\t", "The Lord of the Rings", "The Catcher in the Rye",
"The Great Gatsby", "The Lion and the Witch", "Lord of the Flies", "Animal Farm\t", "Catch-22\t", "The Grapes of Wrath" };



class Book {
private:
    string name, genre, author;
    int number_of_scores, age_restriction, reader_scores[max_reader_scores], size, in_stock, people_used;
    double time_in_hands;
public:
    string genre_getter() {
        return genre;
    }
    int age_restr_getter() {
        return age_restriction;
    }
    int size_getter() {
        return size;
    }
    int in_stock_getter() {
        return in_stock;
    }
    double average_time_in_hands_getter() {
        if (people_used == 0)
            return 0;
        return time_in_hands / people_used;
    }


    void time_in_hands_setter(int time) {
        time_in_hands += time;
        people_used++;
    }

    void in_stock_setter(int y) {
        in_stock = y;
    }
    void reader_score_setter(int score) {
        reader_scores[number_of_scores] = score;
        number_of_scores++;
    }


    double average_reader_score_getter() {
        int i = 0;
        double average_score = 0;
        for (i = 0; i < number_of_scores; i++) {
            average_score += reader_scores[i];
        }
        if (i == 0)
            return 0;
        return average_score/i;
    }

    void book_info_printing() {
        cout << name << "\t\t" << genre << "\t\t" << author << "\t\t" << size << "\t\t" << age_restriction << "\t\t" << in_stock << "\t\t" << people_used << "\t\t" << average_reader_score_getter() << "\t\t\t" << average_time_in_hands_getter() << endl;
    }

    Book(string name_value, string genre_value, string author_value, int size_value, int age_restriction_value) :
        name(name_value), genre(genre_value), author(author_value), size(size_value), age_restriction(age_restriction_value), in_stock(1), number_of_scores(0), people_used(0), time_in_hands(0) {}
};



class Visitor {
private:
    int age, reading_speed, readed_books_number, days_reading, id_of_his_book, days_reading_at_start;
    string size_preference, genre_preference;
public:
    int readed_books_ids[max_readed_books];
    int age_getter() {
        return age;
    }
    string size_preference_getter() {
        return size_preference;
    }
    string genre_preference_getter() {
        return genre_preference;
    }
    /*int* readed_ids_getter() {?????
        return readed_books_ids;
    }*/
    int readed_books_number_getter() {
        return readed_books_number;
    }
    int days_reading_getter() {
        return days_reading;
    }
    int days_reading_at_start_getter() {
        return days_reading_at_start;
    }
    void day_of_reading_passes() {
        days_reading--;
    }
    int id_of_his_book_getter() {
        return id_of_his_book;
    }

    void reading_book(Book* book, int book_id) {
        days_reading = book->size_getter() / reading_speed + 1;
        days_reading_at_start = days_reading;
        readed_books_ids[readed_books_number] = book_id;
        readed_books_number++;
        book->in_stock_setter(0);
        id_of_his_book = book_id;
    }

    void return_book(Book* book) {
        book->time_in_hands_setter(days_reading_at_start - days_reading);
        book->in_stock_setter(1);
        book->reader_score_setter(1 + rand() % 5);
        id_of_his_book = -1;
    }


    Visitor(int age_value, int reading_speed_value, string size_preference_value, string genre_preference_value) :
        age(age_value), reading_speed(reading_speed_value), size_preference(size_preference_value), genre_preference(genre_preference_value), days_reading(0), readed_books_number(0), id_of_his_book(-1) {}
};



class Library {
private:
    Book* books_list[books_q];
    Visitor* visitors_list[visitors_q];
public:
    Book* book_getter(int book_number) {
        return books_list[book_number];
    }

    Visitor* visitor_getter(int visitor_number) {
        return visitors_list[visitor_number];
    }

    void book_list_generation() {
        int i = 0, name_random = 0, genre_random = 0, author_random = 0, size_random = 0, age_restriction_random = 0;
        for (i = 0; i < books_q; i++) {
            name_random = rand() % 10;
            genre_random = rand() % 4;
            author_random = rand() % 10;
            size_random = 50 + rand() % 600;
            age_restriction_random = -1;
            while ((age_restriction_random % 6) != 0)
                age_restriction_random = 6 + rand() % 13;
            books_list[i] = new Book(book_names[name_random], genre_list[genre_random], authors_list[author_random], size_random, age_restriction_random);
        }
    }

    void visitors_list_generation() {
        int i = 0, genre_random = 0, size_random = 0, age_random = 0, reading_speed_random = 0;
        for (i = 0; i < visitors_q; i++) {
            genre_random = rand() % 4;
            size_random = rand() % 3;
            age_random = 6 + rand() % 40;
            reading_speed_random = 10 + rand() % 51;
            visitors_list[i] = new Visitor(age_random, reading_speed_random, size_preferences[size_random], genre_list[genre_random]);
        }
    }

    void book_list_printing() {
        int i = 0;
        cout << "ID\tName\t\t\t\tGenre\t\t\tAuthor\t\t\tSize\t\tAge restr\tIn stock\tTimes in hands\tAverage score\t\tAverage time in hands" << endl;
        for (i = 0; i < books_q; i++) {
            cout << i << "\t";
            books_list[i]->book_info_printing();
        }
    }

    int get_cool_book_id(Visitor* visitor) {
        int visitor_age = visitor->age_getter();
        string fav_size = visitor->size_preference_getter();
        string fav_genre = visitor->genre_preference_getter();
        //int* readed_ids = visitor->readed_ids_getter(); ?????

        int readed_number = visitor->readed_books_number_getter();

        int i = 0, j = 0, shtcounter = 0;
        for (i = 0; i < books_q; i++) {
            shtcounter = 0;
            if (books_list[i]->in_stock_getter() == 0)
                continue;
            for (j = 0; j < readed_number; j++) {
                if (visitor->readed_books_ids[j] == i)
                    shtcounter++;
            }
            if (shtcounter > 0)
                continue;
            if (visitor_age < books_list[i]->age_restr_getter())
                continue;
            if (fav_size == size_preferences[0]) {
                if (books_list[i]->size_getter() < 500) {
                    continue;
                }
            }
            else if (fav_size == size_preferences[1]) {
                if (books_list[i]->size_getter() > 500 || books_list[i]->size_getter() < 100)
                    continue;
            }
            else if (fav_size == size_preferences[2]) {
                if (books_list[i]->size_getter() > 100)
                    continue;
            }
            if (books_list[i]->genre_getter() != fav_genre)
                continue;
            return i;
        }
        return -1;
    }
};




int main(){
    srand(time(NULL));
    int i = 0, j = 0, days_counter = 0, visitors_this_day = 0, visitors_with_books = 0, cool_book_id = 0;
    Visitor* visitor_var;
    Library best_library;
    best_library.book_list_generation();
    best_library.visitors_list_generation();
    for (days_counter = 0; days_counter < days_for_simulation; days_counter++) {
        visitors_with_books = 0;
        visitors_this_day = 1 + rand() % 5;
        for (i = 0; i < visitors_q; i++) {
            visitor_var = best_library.visitor_getter(i);
            if (visitor_var->days_reading_getter() == 0) {
                if (visitor_var->id_of_his_book_getter() != -1)
                    visitor_var->return_book(best_library.book_getter(visitor_var->id_of_his_book_getter()));
                cool_book_id = best_library.get_cool_book_id(visitor_var);
                if (cool_book_id == -1)
                    continue;
                visitor_var->reading_book(best_library.book_getter(cool_book_id), cool_book_id);
                visitors_with_books++;
            }
            if (visitors_with_books == visitors_this_day)
                break;
        }
        for (i = 0; i < visitors_q; i++) {
            visitor_var = best_library.visitor_getter(i);
            if (visitor_var->days_reading_getter() > 0)
                visitor_var->day_of_reading_passes();
        }
    }
    for (i = 0; i < visitors_q; i++) {
        visitor_var = best_library.visitor_getter(i);
        if (visitor_var->id_of_his_book_getter() != -1)
            visitor_var->return_book(best_library.book_getter(visitor_var->id_of_his_book_getter()));
    }
    best_library.book_list_printing();
}


