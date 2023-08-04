#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <typeinfo>

using namespace std;

class Video
{

public:
    string id;
    string name;
    string genre;
    int length;
    float rating;
    string comments;

    // Default constructor
    Video()
    {
        id = "";
        name = "";
        genre = "";
        length = 0;
        rating = 0;
        comments = "";
    }

    Video(string i, string n, string g, int l, float r, string c)
    {
        id = i;
        name = n;
        length = l;
        genre = g;
        rating = r;
        comments = c;
    }

    void print()
    {
        cout << setw(10) << id << left << setw(35) << name << left << setw(10)
             << genre << left << setw(10) << length << left << setw(15) << rating
             << left << setw(5) << comments << left << endl;
    }

    void display_headline()
    {
        cout << setw(10) << left << "ID" << setw(35) << left << "NAME" << left
             << setw(10) << "GENRE" << left << setw(10) << "LENGTH" << left
             << setw(15) << "RATING" << left << setw(5) << "COMMENTS" << left
             << endl;
    }

    // This function compares if the value given is more than 0 and less than 5
    bool valid_rating(float rating)
    {
        if (rating >= 0 && rating <= 5)
        {
            return true;
        }

        return false;
    }

    void display(Video videos[], int size)
    {
        display_headline();
        for (int i = 0; i < size; i++)
        {
            videos[i].print();
        }
    }

    void save(Video videos[], int size, string filename)
    {
        ofstream f;
        f.open(filename);

        for (int i = 0; i < size; i++)
        {
            f << videos[i].id << "," << videos[i].name << "," << videos[i].genre << "," << videos[i].length << "," << videos[i].rating << "," << videos[i].comments << endl;
        }
    }

    void filter(Video videos[], int size, string ngenre)
    {
        display_headline();
        int j = 0;
        for (int i = 0; i < size; i++)
        {
            if (videos[i].genre == ngenre)
            {
                videos[i].print();
                j++;
            }
        }

        if (j == 0)
        {
            cout << "No item for that genre was found." << endl;
        }
    }
};

class Movie : public Video
{
public:
    // Default constructor
    Movie() : Video("", "", "", 0, 0, "") {}
    Movie(string i, string n, string g, int l, float r, string c) : Video(i, n, g, l, r, c)
    {
    }

    void read(Movie *movies[], int size)
    {
        string row[6];
        string word;
        string line;

        ifstream f;
        f.open("movies.csv");

        int i = 0;
        while (getline(f, line))
        {
            stringstream ss(line);

            int j = 0;
            while (getline(ss, word, ','))
            {
                row[j] = word;
                j++;
            }
            movies[i] = new Movie(row[0], row[1], row[2], stoi(row[3]), stof(row[4]), row[5]);
            i++;
        }

        f.close();
    }

    Movie *search(Movie *movies[], int size, string search_term)
    {
        // Search for a movie based on the search term
        for (int i = 0; i < size; i++)
        {
            if (movies[i]->name == search_term)
            {
                return movies[i];
            }
        }

        return nullptr;
    }

    void evaluate(Movie *movies[], int size)
    {
        string name;
        float rating;

        cout << "Enter movie name: ";
        getline(cin, name);

        // Get a pointer to the movie object using the search function
        Movie *m = search(movies, size, name);

        if (m == nullptr)
        {
            cout << "Movie with that name was not found." << endl;
            return;
        }

        cout << "Enter your rating for the movie: ";
        cin >> rating;
        cin.ignore();

        // Change the movie's rating if it is valid
        if (valid_rating(rating))
        {
            m->rating = rating;
            m->print();
        }
        else
        {
            cout << "Rating must be between 0 and 5" << endl;
        }
    }

    // Function for changing a Movie pointer array to a normal array
    Movie *pointer_to_normal(Movie *movies[], int size)
    {
        // Declare new array of the same size
        Movie *normal_array = new Movie[size];

        // Change every pointer object in the array to its object value
        for (int i = 0; i < size; i++)
        {
            normal_array[i] = *movies[i];
        }

        return normal_array;
    }

    void filter(Movie movies[], int size)
    {
        string genre;
        cout << "Enter the genre for the movies: ";
        getline(cin, genre);

        Video::filter(movies, size, genre);
    }
};

class Serie : public Video
{
public:
    // Default constructor
    Serie() : Video("", "", "", 0, 0, "") {}
    Serie(string i, string n, string g, int l, float r, string c) : Video(i, n, g, l, r, c)
    {
    }

    void read(Serie *series[], int size)
    {
        string row[6];
        string word;
        string line;

        ifstream f;
        f.open("series.csv");

        int i = 0;
        while (getline(f, line))
        {
            stringstream ss(line);

            int j = 0;
            while (getline(ss, word, ','))
            {
                row[j] = word;
                j++;
            }
            series[i] = new Serie(row[0], row[1], row[2], stoi(row[3]), stof(row[4]), row[5]);
            i++;
        }

        f.close();
    }

    Serie *search(Serie *series[], int size, string search_term)
    {
        // Search for a series based on the search term
        for (int i = 0; i < size; i++)
        {
            if (series[i]->name == search_term)
            {
                return series[i];
            }
        }

        return nullptr;
    }

    void evaluate(Serie *series[], int size)
    {
        string name;
        float rating;

        cout << "Enter series name: ";
        getline(cin, name);

        // Get a pointer to the Series object using the search function
        Serie *s = search(series, size, name);

        if (s == nullptr)
        {
            cout << "Series with that name was not found." << endl;
            return;
        }

        cout << "Enter your rating for the series: ";
        cin >> rating;
        cin.ignore();

        // If rating is valid change the Series rating
        if (valid_rating(rating))
        {
            s->rating = rating;
            s->print();
        }
        else
        {
            cout << "Rating must be between 0 and 5" << endl;
        }
    }

    // Change a Series pointer array to a normal array
    Serie *pointer_to_normal(Serie *series[], int size)
    {
        // Declare a new Series array
        Serie *normal_array = new Serie[size];

        // Change every pointer object to its object value
        for (int i = 0; i < size; i++)
        {
            normal_array[i] = *series[i];
        }

        return normal_array;
    }

    void filter(Serie series[], int size)
    {
        string genre;
        cout << "Enter the genre for the series: ";
        getline(cin, genre);

        Video::filter(series, size, genre);
    }
};

int main()
{
    // This ones are for call the functions
    Video vc("", "", "", 0, 0, "");
    Movie mc("", "", "", 0, 0, "");
    Serie sc("", "", "", 0, 0, "");

    // Pointer arrays for storing all the movies and series
    Movie *movies[30];
    Serie *series[29];

    // Read the movies and series files and save each object to their array
    mc.read(movies, 30);
    sc.read(series, 29);

    int optionSelected = 0;
    bool validOption = false;

    //......................Menu of Tecflix......................//
    cout << "Welcome to Teclfix" << endl;

    while (true)
    {
        validOption = false;
        while (!validOption)
        {
            cout << "Please select an option: " << endl;
            cout << "1. Display all videos" << endl;
            cout << "2. Display all movies" << endl;
            cout << "3.Display all movies by genre" << endl;
            cout << "4. Search movie by name" << endl;
            cout << "5. Evaluate movie between 0-5" << endl;
            cout << "6. Save the changes in the movies file" << endl;
            cout << "7. Display all series" << endl;
            cout << "8. Display series by genre" << endl;
            cout << "9. Search series by name" << endl;
            cout << "10. Evaluate series between 0-5" << endl;
            cout << "11. Save the changes in the series file" << endl;
            cout << "12. Exit" << endl;
            cin >> optionSelected;

            cin.ignore();

            if (cin.fail() || optionSelected < 1 || optionSelected > 12)
            {
                cin.clear();
                cout << "Invalid option. Please enter a number between 1 and 12." << endl
                     << endl;
            }

            else
            {
                validOption = true;
            }
        }

        //......................Option selected......................//

        if (optionSelected == 1)
        {
            cout << "Here you have all the videos: " << endl;
            cout << endl;
            cout << "Movies" << endl;
            mc.display(mc.pointer_to_normal(movies, 30), 30);
            cout << endl;
            cout << "Series" << endl;
            vc.display(sc.pointer_to_normal(series, 29), 29);
            cout << endl;
        }
        else if (optionSelected == 2)
        {
            cout << "Here you have all the movies: " << endl;
            vc.display(mc.pointer_to_normal(movies, 30), 30);
            cout << endl;
        }

        else if (optionSelected == 3)
        {
            cout << "Here you have all the movies by genre: " << endl;
            mc.filter(mc.pointer_to_normal(movies, 30), 30);
            cout << endl;
        }

        else if (optionSelected == 4)
        {
            string name;
            cout << "Enter the movie name: ";
            getline(cin, name);

            Movie *m = mc.search(movies, 30, name);

            if (m != nullptr)
            {
                cout << endl;
                vc.display_headline();
                m->print();
            }
            else
            {
                cout << "Movie with that name was not found." << endl;
            }

            cout << endl;
        }

        else if (optionSelected == 5)
        {
            cout << "Here you can evaluate the movie between 0-5: " << endl;
            mc.evaluate(movies, 30);
            cout << endl;
        }

        else if (optionSelected == 6)
        {
            cout << "Here you can save the changes in the movies file: " << endl;
            vc.save(mc.pointer_to_normal(movies, 30), 30, "movies.csv");
        }

        else if (optionSelected == 7)
        {
            cout << "Here you have all the series:" << endl;
            vc.display(sc.pointer_to_normal(series, 29), 29);
            cout << endl;
        }

        else if (optionSelected == 8)
        {
            cout << "Here you have all the series by genre" << endl;
            sc.filter(sc.pointer_to_normal(series, 29), 29);
            cout << endl;
        }

        else if (optionSelected == 9)
        {
            string name;
            cout << "Enter the series name: ";
            getline(cin, name);

            Serie *s = sc.search(series, 29, name);

            if (s != nullptr)
            {
                cout << endl;
                vc.display_headline();
                s->print();
            }
            else
            {
                cout << "Series with that name was not found." << endl;
            }

            cout << endl;
        }

        else if (optionSelected == 10)
        {
            cout << "Here you can evaluate the series between 0-5: " << endl;
            sc.evaluate(series, 30);
        }

        else if (optionSelected == 11)
        {
            cout << "Here you can save the changes in the series file: " << endl;
            vc.save(sc.pointer_to_normal(series, 29), 29, "series.csv");
        }

        else if (optionSelected == 12)
        {
            cout << "Goodbye, see you soon." << endl;
            break;
        }
        else
        {
            cout << "Invalid Input" << endl;
        }
    }

    return 0;
};
