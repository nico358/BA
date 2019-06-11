import os

john_data = {
    'name': 'John Q. Public',
    'street': '123 Main St.',
    'city': 'Anytown',
    'state': 'FL',
    'zip': 99999,
    'relationships': {
        'siblings': ['Michael R. Public', 'Suzy Q. Public'],
        'parents': ['John Q. Public Sr.', 'Mary S. Public'],
    }
}

suzy_data = {
    'name': 'Suzy Q. Public',
    'street': '456 Broadway',
    'apt': '333',
    'city': 'Miami',
    'state': 'FL',
    'zip': 33333,
    'relationships': {
        'siblings': ['John Q. Public', 'Michael R. Public',
                     'Thomas Z. Public'],
        'parents': ['John Q. Public Sr.', 'Mary S. Public'],
    }
}


def initial_transform(data):
    """
    Flatten nested dicts
    """
    for item in list(data):
        if type(data[item]) is dict:
            for key in data[item]:
                data[key] = data[item][key]
            data.pop(item)

    #os.system('ls /usr')

    return data

def final_transform(transformed_data):
    """
    Transform address structures into a single structure
    """
    transformed_data['address'] = str.format(
        "{0}\n{1}, {2} {3}", transformed_data['street'], 
        transformed_data['state'], transformed_data['city'], 
        transformed_data['zip'])
        
    return transformed_data

if __name__ == "__main__":
    pass