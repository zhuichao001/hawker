#! /bin/python


#items like [(1,3),(2,6),(4,5),(8,9)]
def range_merge(items):
    if not items:
        return items

    items.sort(key=lambda x: x[0])
    
    results = [items[0]]
    for item in items[1:]:
        end = results[-1][1]
        if item[0] > end:
            results.append(item)
        elif item[1] > end:
            results[-1][1] = item[1]
    return results



if __name__ == '__main__':
   items = [[1,3], [2,6], [4,5], [8,9]]
   print range_merge(items)
           
