

#include <iostream>
using namespace std;
#include"treesHeader.h"



const int MAX_LENGTH = 256;




void makeFolder(String& folder, string filename, int columnIndex)
{
    ifstream file(filename);
    if (!file) {
        cout << "Error: File could not be opened!" << endl;
        return;
    }
    int counter = 0;
    String line;
    int lineNumber = 1;

    String caller;
    char buffer[1024]{ '\0' };
    caller.mygetline(file, buffer, 1024);
    int j = 0;
    while (buffer[j] != '\0')
    {

        if (buffer[j] == ',')
        {

            counter++;
            if (counter - columnIndex == 1)
            {
                break;
            }
            folder.clear();
        }
        else
        {
            folder = folder + buffer[j];
        }
        j++;
    }
    j = 0;
    while (folder[j] != '\0')
    {
        if (folder[j] == ' ' || folder[j] == '/' || folder[j] == '\\') {
            folder[j] = '_';
        }
        j++;
    }
    if (!fs::exists(folder.constCharPointer()))
    {
        fs::create_directory(folder.constCharPointer());
    }

    file.close();
}

void makeDefaultBranch()
{
    String repository = "Repository";
    if (!fs::exists(repository.constCharPointer()))
    {
        fs::create_directory(repository.constCharPointer());
    }
    fs::current_path(repository.constCharPointer());
    String branch = "Main";
    if (!fs::exists(branch.constCharPointer()))
    {
        fs::create_directory(branch.constCharPointer());
    }
    fs::current_path(branch.constCharPointer());
    std::ofstream file("commitLog.txt");
    if (file.is_open())
    {
        file.close();
    }


}

void makeNewBranch(AVLTree& Node, String& branch, RBTree rb)
{
    // Navigate to the parent directory
    fs::current_path(fs::current_path().parent_path());

    // Check if the destination folder exists; create or clear it
    if (!fs::exists(branch.constCharPointer()))
    {
        fs::create_directory(branch.constCharPointer()); // Create the branch folder if it doesn't exist
    }
    else
    {
        for (const auto& entry : fs::directory_iterator(branch.constCharPointer()))
        {
            fs::remove_all(entry); // Remove files and subdirectories in the existing branch folder
        }
    }

    // Path to the source folder (Main) and the target folder (branch)
    fs::path sourceFolder = fs::current_path() / "Main";
    fs::path targetFolder = fs::current_path() / branch.constCharPointer();

    // Ensure the source folder exists
    if (fs::exists(sourceFolder) && fs::is_directory(sourceFolder))
    {
        // Copy all contents from the source folder to the target folder
        for (const auto& entry : fs::directory_iterator(sourceFolder))
        {
            fs::path targetPath = targetFolder / entry.path().filename();
            if (fs::is_directory(entry.path()))
            {
                fs::copy(entry.path(), targetPath, fs::copy_options::recursive);
            }
            else
            {
                fs::copy(entry.path(), targetPath);
            }
        }

        // Navigate to the destination folder and write Node.root to Root.txt
        fs::current_path(branch.constCharPointer());
        std::ofstream file("Root.txt");
        if (file.is_open())
        {
            file << Node.root;
            file.close();
        }
        else
        {
            std::cerr << "Error: Could not open or create Root.txt in the branch folder." << std::endl;
        }
        std::ofstream filee("commitLog.txt");
        if (filee.is_open())
        {
            filee.close();
        }

    }
    else
    {
        std::cerr << "Error: Source folder 'Main' does not exist or is not a directory." << std::endl;
    }
}


void SwitchBranch(AVLTree& Node, String& to, RBTree& rb)
{

    ofstream file("Root.txt");
    file << Node.root;
    file.close();
    fs::current_path(fs::current_path().parent_path());
    // Check if the destination folder exists
    if (!fs::exists(to.constCharPointer()))
    {
        cerr << "Error: Destination folder '" << to << "' does not exist." << std::endl;
        return;
    }
    fs::current_path(to.constCharPointer());
    cout << "Changed current directory to: " << fs::current_path() << endl;
    ifstream filee("Root.txt");
    String filePath;
    char line[1024]{ '\0' };
    filePath.mygetline(filee, line, 1024);
    Node.root = line;
    filee.close();

}

void deletion(bool occur, char** queries, int rows, String folder, int tree, AVLTree& avnode, RBTree& rb, int choice)
{
    const int r = 20;
    int col[r];
    char** toFind = new char* [rows];
    for (int i = 0; i < rows; i++)
    {
        toFind[i] = new char[25];
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < 25; j++) {
            toFind[i][j] = '\0';
        }
    }
    String ref = queries[1];
    String folder2 = folder + '/';
    ref = folder2 + ref;
    ref = ref + ".txt";

    int k = 0;
    for (int i = 4; i < rows; i += 3)
    {
        if (queries[i][0] != '*')
        {
            toFind[k] = queries[i];
            col[k] = queries[i - 1][0] - '0';

            k++;

        }
    }


    bool deleteKey = false;
    for (int i = 3; i < rows; i += 3)
    {
        if (queries[i][0] != '*')
        {
            deleteKey = true;
        }
    }
    if (!deleteKey && !occur && tree == 1 && choice == 1)
    {
        avnode.deleteNode(ref);
        ofstream file("commitLog.txt", ios::app);
        file << "Deleted " << ref << endl;
        file.close();

        return;
    }
    else if (!deleteKey && !occur && tree == 2 && choice == 1)
    {
        rb.deleteNode(ref);
        ofstream file("commitLog.txt", ios::app);
        file << "Deleted " << ref << endl;
        file.close();
        return;
    }
    else if (!deleteKey)
    {
        String tempfilename = folder2 + "temp.txt";
        ofstream to(tempfilename.constCharPointer());
        ifstream file(ref.constCharPointer());
        String caller;
        String data;
        int linenum = 1;
        bool nothingdeleted = true;
        while (caller.getline(file, data))
        {
            if (choice == 1 && occur)
            {

                if (linenum > 5)
                {
                    if (!(data == '-') && nothingdeleted)
                    {
                        to << "-" << endl;
                        nothingdeleted = false;
                        ofstream file("commitLog.txt", ios::app);
                        file << "Erased " << data << " file " << ref << endl;
                        file.close();

                    }
                    else
                    {
                        to << data << endl;
                    }

                }
                else
                {
                    to << data << endl;
                }

            }

            if (choice == 3)
            {
                if (linenum > 5)
                {
                    cout << data << endl;
                    if (occur)
                        break;
                }
            }
            linenum++;
        }
        file.close();
        to.close();
        if (choice == 1 && occur)
        {
            std::filesystem::remove(ref.constCharPointer());
            std::filesystem::rename(tempfilename.constCharPointer(), ref.constCharPointer());
        }
        if (choice == 1 && (linenum == 7 || nothingdeleted) && occur)
        {
            if (tree == 1 && choice == 1)
            {
                avnode.deleteNode(ref);
            }
            else if (tree == 2 && choice == 1)
            {
                rb.deleteNode(ref);
            }
        }



        return;
    }
    if (deleteKey)
    {
        ifstream file(ref.constCharPointer());
        String tempfilename = folder2 + "temp.txt";
        ofstream to(tempfilename.constCharPointer());
        String data;
        String caller;

        int i = 0;;
        int linenum = 1;
        while (caller.getline(file, data)) // Read each line
        {
            bool querymatched = true; // Initialize querymatched as true for each line

            // Handle lines 1 to 5
            if (linenum <= 5 && choice == 1)
            {
                to << data << endl;
            }

            // Handle lines after line 5
            if (linenum > 5)
            {
                for (int index = 0; index < k; index++) // Loop through all "toFind" elements
                {
                    i = 2; // Start reading data at index 2
                    int j = 0; // Index for matching "toFind" string
                    String temp;
                    int tempcol = 0;

                    // Parse the line to check for a match
                    while (data[i] != '\0')
                    {
                        if (data[i] == ',') // Column delimiter
                        {
                            tempcol++;
                            temp = '\0'; // Reset temp for the next column
                        }
                        else if (tempcol == col[index]) // Check the target column
                        {
                            if (data[i] != toFind[index][j]) // Character mismatch
                            {
                                querymatched = false; // Mark querymatched as false
                                break; // Exit the current loop
                            }
                            j++; // Move to the next character in "toFind"
                        }
                        i++;
                    }

                    // Exit the loop early if a mismatch is found
                    if (!querymatched)
                    {
                        break;
                    }
                }

                // Handle the line based on query match result and choice
                if (querymatched)
                {
                    if (choice == 3)
                    {
                        cout << data << endl;
                    }
                    else if (choice == 1)
                    {
                        to << "-" << endl;
                        ofstream file("commitLog.txt", ios::app);
                        file << "Erased " << data << "file " << endl;
                        file.close();
                    }
                }
                else if (choice == 1) // Line doesn't match, write it as-is
                {
                    to << data << endl;
                }
            }

            linenum++; // Increment line number
        }


        file.close();
        to.close();
        if (choice == 1)
        {
            std::filesystem::remove(ref.constCharPointer());
            std::filesystem::rename(tempfilename.constCharPointer(), ref.constCharPointer());
        }
    }
}

void add(char** col, int total_col, int selected_index, String& folder, int tree, AVLTree& avlnode, RBTree& rb, const char* filenames) {
    ifstream filee(filenames);
    if (!filee)
    {
        cout << "Error: File could not be opened!" << endl;
        return;
    }
    char bufferr[MAX_LENGTH];
    filee.getline(bufferr, MAX_LENGTH);
    String ans;
    String combine;
    String key;
    int colIndex = 0;
    char* context = nullptr;
    char* token = strtok_s(bufferr, ",", &context);
    int i = 0;
    while (token)
    {
        cout << "Enter  " << token << endl;
        cin >> ans;
        if (i == selected_index) {
            key = ans;
        }
        if (i == (total_col - 1))
        {
            combine = combine + ans;

        }
        else {
            combine = combine + ans;
            combine = combine + ',';
        }
        token = strtok_s(nullptr, ",", &context);
        i++;
    }
    filee.close();



    String name = folder + '/';
    String name1 = name + key;
    String name2 = name1 + ".txt";

    if (tree == 1) {

        avlnode.insertIterative(avlnode.root, name2, "");
        ofstream outFile(name2.constCharPointer(), ios::app);
        if (outFile)
        {
            outFile << "111" << ":" << combine << endl;
            outFile.close();
        }
        else
        {
            cout << "Error: Could not create file for " << key << endl;
        }
        outFile.close();
    }
    else {
        rb.insertNodeWithLineData(key, name2, combine);
        ofstream outFile(name2.constCharPointer(), ios::app);
        if (outFile)
        {
            outFile << "111" << ":" << combine << endl;
            outFile.close();
        }
        else
        {
            cout << "Error: Could not create file for " << key << endl;
        }
        outFile.close();
    }


    ofstream file("commitLog.txt", ios::app);
    file << "Added " << key << " in " << folder << endl;

    file.close();
    cout << endl;

}
void queries(char**& col, int no_of_col, int first_col, int tree, AVLTree& avNode, String& foldername, RBTree& rb, const char* filenames)
{

    char** queries = new char* [no_of_col * 3];
    for (int i = 0; i < no_of_col * 3; i++) {
        queries[i] = new char[25];
    }
    for (int i = 0; i < no_of_col * 3; i++) {
        for (int j = 0; j < 25; j++) {
            queries[i][j] = '\0';
        }
    }

    String ans;
    String answer;
    int index = 0;
    char y;
    bool range = false;
    bool start = false;
    bool end = false;
    bool svd = false;
    cout << "-----------QUERIES------------" << endl;
    cout << "do you want to proivde range (y/n) of " << endl;
    for (int i = 0; col[first_col][i] != '\0'; i++) {
        cout << col[first_col][i];
    }
    cout << endl;
    cin >> y;
    if (y == 'y' || y == 'Y') {
        range = true;
    }
    char c = '0' + first_col;
    queries[index][0] = c;
    index++;
    if (range)
    {
        cout << "Do you want to provide start ?(y/n)" << endl;
        cin >> y;
        if (y == 'y' || y == 'Y') {
            start = true;
        }
        if (start) {
            cout << "Provide the starting value of ";
            for (int i = 0; col[first_col][i] != '\0'; i++) {
                cout << col[first_col][i];
            }
            cout << endl;
            cin >> ans;

            for (int i = 0; ans[i] != '\0'; i++) {
                queries[index][i] = ans[i];
            }
            index++;
            start = false;
        }
        else {
            queries[index][0] = '*';
            index++;
        }
        cout << "Do you want to provide end ?(y/n)" << endl;
        cin >> y;
        if (y == 'y' || y == 'Y') {
            end = true;
        }
        if (end) {
            cout << "Provide the ending value of ";
            for (int i = 0; col[first_col][i] != '\0'; i++) {
                cout << col[first_col][i];
            }
            cout << endl;
            cin >> ans;
            for (int i = 0; ans[i] != '\0'; i++) {
                queries[index][i] = ans[i];
            }
            index++;
            end = false;
        }
        else {

            queries[index][0] = '*';
            index++;
        }
        range = false;
    }
    else {
        cout << "do you want to proivde single value(y/n) " << endl;
        cin >> y;
        if (y == 'y' || y == 'Y') {
            svd = true;
        }

        if (svd)
        {
            cout << "Enter the ";
            for (int i = 0; col[first_col][i] != '\0'; i++) {
                cout << col[first_col][i];
            }
            cout << endl;
            cin >> ans;
            for (int i = 0; ans[i] != '\0'; i++) {
                queries[index][i] = ans[i];
            }
            index++;
            queries[index][0] = '*';
            index++;
            svd = false;
        }
        else {

            queries[index][0] = '*';
            index++;
            queries[index][0] = '*';
            index++;
        }
    }


    for (int j = 0; j < no_of_col; j++) {

        if (j != first_col)
        {

            cout << "do you want to proivde range (y/n)" << endl;
            for (int i = 0; col[j][i] != '\0'; i++) {
                cout << col[j][i];
            }
            cout << endl;
            cin >> y;
            if (y == 'y' || y == 'Y') {
                range = true;
            }



            if (range)
            {
                char temp = '0' + j;
                queries[index][0] = temp;
                index++;
                cout << "Do you want to provide start ?(y/n)" << endl;
                cin >> y;
                if (y == 'y' || y == 'Y') {
                    start = true;
                }
                if (start) {
                    cout << "Provide the starting value of ";
                    for (int i = 0; col[j][i] != '\0'; i++)
                    {
                        cout << col[j][i];
                    }
                    cout << endl;
                    cin >> ans;

                    for (int i = 0; ans[i] != '\0'; i++) {
                        queries[index][i] = ans[i];
                    }
                    index++;
                    start = false;
                }
                else {
                    queries[index][0] = '*';
                    index++;
                }
                cout << "Do you want to provide end ?(y/n)" << endl;
                cin >> y;
                if (y == 'y' || y == 'Y') {
                    end = true;
                }
                if (end) {
                    cout << "Provide the ending value of ";
                    for (int i = 0; col[j][i] != '\0'; i++) {
                        cout << col[j][i];
                    }
                    cout << endl;
                    cin >> ans;
                    for (int i = 0; ans[i] != '\0'; i++) {
                        queries[index][i] = ans[i];
                    }
                    index++;
                    end = false;
                }
                else {

                    queries[index][0] = '*';
                    index++;
                }
                range = false;
            }
            else {
                cout << "do you want to proivde single value(y/n) " << endl;
                cin >> y;
                if (y == 'y' || y == 'Y') {
                    svd = true;
                }
                if (svd)
                {
                    char temp = '0' + j;
                    queries[index][0] = temp;
                    index++;
                    cout << "Enter the ";
                    for (int i = 0; col[j][i] != '\0'; i++) {
                        cout << col[j][i];
                    }
                    cout << endl;
                    cin >> ans;
                    for (int i = 0; ans[i] != '\0'; i++) {
                        queries[index][i] = ans[i];
                    }
                    index++;
                    queries[index][0] = '*';
                    index++;
                    svd = false;
                }
                else {
                    queries[index][0] = '*';
                    index++;
                    queries[index][0] = '*';
                    index++;
                    queries[index][0] = '*';
                    index++;
                }
            }
        }
    }
    cout << endl;

    for (int i = 0; i < no_of_col * 3; i++) {
        for (int j = 0; queries[i][j] != '\0'; j++) {
            cout << queries[i][j];
        }
        cout << endl;
    }
    bool firstoccurence = false;
    int editcolomn;
    String editval;
    char choose;
    cout << "Multiple (m) or First Occurence (f)" << endl;
    cin >> choose;
    if (choose == 'f') {
        firstoccurence = true;
    }
    int choice;
    cout << "Enter your preferences what operation you want to perform:" << endl;
    cout << "1.Delete      2.Add     3.Select" << endl;
    cin >> choice;
    // AVL tree calls


    if (choice == 2)
    {
        add(col, no_of_col, first_col, foldername, tree, avNode, rb, filenames);
    }
    else
        deletion(firstoccurence, queries, no_of_col * 3, foldername, tree, avNode, rb, choice);




}


void OutputMenu(const char* filename, int& columnIndex, int& no_of_col)
{
    ifstream filee(filename);
    if (!filee)
    {
        cout << "Error: File could not be opened!" << endl;
        return;
    }
    char bufferr[MAX_LENGTH];
    filee.getline(bufferr, MAX_LENGTH);
    cout << "Columns in the CSV file:\n";
    int colIndex = 0;
    char* context = nullptr;
    char* token = strtok_s(bufferr, ",", &context);
    while (token)
    {
        cout << colIndex++ << ": " << token << endl;
        token = strtok_s(nullptr, ",", &context);
    }
    no_of_col = colIndex;
    cout << "Enter the column index to process: ";
    cin >> columnIndex;
    filee.close();
}

void showCommitLog()
{
    ifstream read("commitLog.txt");
    String caller;
    char buffer[1024]{ '\0' };
    while (caller.mygetline(read, buffer, 1024))
    {
        int i = 0;
        while (buffer[i] != '\0') {
            cout << buffer[i];
            i++;
        }
        cout << endl;
    }
    read.close();

}

// Main function
int main()
{
    const char* filename = "C:/Users/HP/source/repos/GitLite/Marks.csv";
    AVLTree Node;
    Node.root = "NULL";
    RBTree rb;
    rb.root = "NULL";
    // Initialize RB tree
    int tree = 0;
    int columnIndex;
    String folderName;
    bool closeProgram = false;
    String initialCommand;
    cout << "Run Init Command to Intilaize a repository of your data" << endl;
    cin >> initialCommand;
    int total_col = 0;
    if (initialCommand == "iNIT" || initialCommand == "init" || initialCommand == "INIT" || initialCommand == "InIt")
    {
        //Referrence Column
        OutputMenu(filename, columnIndex, total_col);
        cout << "Enter Tree Choice:\n1: AVL\n2: Red Black Tree" << endl;
        cin >> tree;

        //INIT command
        makeDefaultBranch();
        makeFolder(folderName, filename, columnIndex);
        if (tree == 1)
        {
            Node.processColumn(columnIndex, filename, folderName);
            ofstream file("Root.txt");
            file << Node.root << endl;
            file.close();
        }
        else if (tree == 2)
        {
            rb.processColumn(columnIndex, filename, folderName);
            ofstream file("Root.txt");
            file << rb.root << endl;
            file.close();
        }
        // make merkle
        makeMerkleTree(folderName);
        //Set root.txt



        while (!closeProgram)
        {
            int choice;
            cout << "Press\n1: Make new Branch of Main\n2: Switch to another Branch\n3: Changes ( Edit, Delete, Select )\n4: Dispaly tree\n5: Show commit log\n6: Close Git" << endl;
            cin >> choice;

            switch (choice)
            {

            case 1:
            {
                //Make branch
                String branchName;
                cout << " Enter name for your Branch" << endl;
                cin >> branchName;

                makeNewBranch(Node, branchName, rb);


                break;
            }
            case 2:
            {
                //Switch Branch
                String to;
                cout << " Enter Branch you want to Work on" << endl;
                cin >> to;
                SwitchBranch(Node, to, rb);




                break;
            }
            case 3:
            {
                // Delete Selected Column
                int columns = 0;
                //char** content = processCSV("mixcase.txt", columns);
                ifstream file1(filename);
                String header;
                header.getline(file1, header);
                file1.close();

                char** colomn = new char* [total_col];
                for (int i = 0; i < total_col; i++) {
                    colomn[i] = new char[50];
                }
                for (int i = 0; i < total_col; i++) {
                    for (int j = 0; j < 50; j++) {
                        colomn[i][j] = '\0';
                    }
                }

                string name_col;
                int rows = 0;
                int j = 0;
                for (int i = 0; i < header.stringSize(); ++i) {

                    if (header[i] == ',') {
                        rows++;
                        j = 0;
                    }
                    else {

                        colomn[rows][j] = header[i];
                        j++;
                    }
                }


                queries(colomn, total_col, columnIndex, tree, Node, folderName, rb, filename);

                //Commit the Change?
                //...
                break;
            }
            case 4:
            {
                //Display Bonus
                cout << "\nDisplaying AVL tree:\n";
                if (tree == 1)
                {
                    Node.displayIterativeS();

                }
                else if (tree == 2)
                {
                    rb.displayIterativeS();
                }

                break;
            }
            case 5:
            {
                showCommitLog();
                break;
            }
            case 6:
            {
                closeProgram = true;
                break;
            }
            case 7:
            {
                //  showCommands();
            }
            }
        }

    }

    return 0;

}


